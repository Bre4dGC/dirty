#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <dirent.h>

#define INITIAL_ROWS 10  // Initial number of lines
#define NAME_SIZE    256 // Maximum file name
#define LINE_LEN     70  // Line length

char *path = "P:/";
wchar_t **files = NULL;
u_short selected_index = 0;
u_short count = 0;

void draw_menu();
void get_catalog();
void update_selection(u_short old_index, u_short new_index);
void handle_input();

int main() 
{
    setlocale(LC_ALL, ""); 
    SetConsoleOutputCP(CP_UTF8);

    printf("\e[?25l"); // Hiding the cursor
    system("cls");

    get_catalog();
    draw_menu();
    handle_input();

    for (u_char i = 0; i < count; i++) {
        free(files[i]); // Free memory for all file name
    }
    free(files); // Free array of pointers
    return 0;
}

void draw_menu() {
    for (u_char i = 0; i < count; i++) {
        printf("\e[%d;1H", i + 1);
        if (i == selected_index) {
            printf(">");
            wprintf(L"%s", files[i]);
            u_short fname_len = wcslen(files[i]);
            for (u_char j = 0; j < LINE_LEN - fname_len; j++) {
                printf("=");
            }
        } else {
            wprintf(L" %s", files[i]);
        }
        printf("\n");
    }
}

// Updating only changed lines
void update_selection(u_short old_index, u_short new_index) {
    wprintf(L"\e[%d;1H %s\e[K", old_index + 1, files[old_index]); // Removes the old discharge

    // Drawing a new selection
    printf("\e[%d;1H>", new_index + 1);
    wprintf(L"%s", files[new_index]);

    u_short fname_len = wcslen(files[new_index]);

    for (u_char j = 0; j < LINE_LEN - fname_len; j++) {
        printf("=");
    }
    printf("\e[K"); // Cleaning the remains of the line
}

// The input processing function from the keyboard
void handle_input() {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD numRead;
    INPUT_RECORD inputRecord;

    while (1) {
        ReadConsoleInput(hConsole, &inputRecord, 1, &numRead);
        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
            u_short old_index = selected_index;
            switch (inputRecord.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (selected_index > 0) selected_index--;
                    break;
                case VK_DOWN:
                    if (selected_index < count - 1) selected_index++;
                    break;
                case VK_RETURN:
                    return;
            }
            if (old_index != selected_index) {
                update_selection(old_index, selected_index);
            }
        }
    }
}

void get_catalog()
{
    u_char capacity = INITIAL_ROWS; // initial capacity of the array

    files = malloc(capacity * sizeof(wchar_t *));
    if (!files) {
        perror("Error: memory allocation failed");
        return;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        perror("Error: catalog opening failed");
        free(files);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // convert `char` into` wchar_t`
        wchar_t wname[NAME_SIZE];
        mbstowcs(wname, entry->d_name, NAME_SIZE);
 
        // If the array is crowded, increase its size
        if (count >= capacity) {
            capacity *= 2;
            files = realloc(files, capacity * sizeof(wchar_t *));
            if (!files) {
                perror("Error: memory allocation failed");
                closedir(dir);
                return;
            }
        }

        // allocate memory under the name of the file and copy it
        files[count] = malloc(NAME_SIZE * sizeof(wchar_t));
        if (!files[count]) {
            perror("Error: memory allocation failed");
            break;
        }
        wcsncpy(files[count], wname, NAME_SIZE - 1);
        files[count][NAME_SIZE - 1] = L'\0';
        count++;
    }
    closedir(dir);
}
