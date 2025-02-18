#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define NUM_ITEMS    8
#define LINE_LEN     25

const wchar_t *menu_items[NUM_ITEMS] = {
    L"Education",
    L"Programming",
    L"Documentation",
    L"Images",
    L"Ideas",
    L"Oh-My-Posh Themes",
    L"Templates",
    L"План обучения"  // Русские символы
};

u_short selected_index = 0;

void draw_menu();
void update_selection(u_short old_index, u_short new_index);
void handle_input();

int main() {
    setlocale(LC_ALL, ""); 
    SetConsoleOutputCP(CP_UTF8);

    printf("\e[?25l"); // Hiding the cursor
    system("cls");
    draw_menu();
    handle_input();
    return 0;
}

void draw_menu() {
    for (u_short i = 0; i < NUM_ITEMS; i++) {
        printf("\e[%d;1H", i + 1); // Moving the cursor
        if (i == selected_index) {
            printf(">");
            wprintf(L"%s", menu_items[i]);
            u_short len = wcslen(menu_items[i]);
            for (u_short j = 0; j < LINE_LEN - len; j++) {
                printf("=");
            }
        } else {
            wprintf(L" %s", menu_items[i]);
        }
        printf("\n");
    }
}

// Updating only changed lines
void update_selection(u_short old_index, u_short new_index) {
    wprintf(L"\e[%d;1H %s\e[K", old_index + 1, menu_items[old_index]); // Removes the old discharge

    // Drawing a new selection
    printf("\e[%d;1H>", new_index + 1);
    wprintf(L"%s", menu_items[new_index]);

    u_short len = len = wcslen(menu_items[new_index]);

    for (u_short j = 0; j < LINE_LEN - len; j++) {
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
                    if (selected_index < NUM_ITEMS - 1) selected_index++;
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
