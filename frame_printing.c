#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MIN_WIDTH  32
#define MIN_HEIGHT 16
#define MAX_WIDTH  200
#define MAX_HEIGHT 100

void get_scr_size();
void print_frame();
void resize_event_loop();
void get_catalog(char *path);

u_short width = 0, height = 0; // Screen size

int main()
{
    system("cls");     // Cleaning the screen
    printf("\e[?25l"); // Turn off the caret

    get_scr_size();      // Get size of screen
    print_frame();       // Printing the frame
    resize_event_loop(); // Start of events handling

    printf("\e[?25h"); // Turn on the caret
    return 0;
}

void resize_event_loop() {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: failed to get console handle\n");
        return;
    }

    DWORD numRead;
    INPUT_RECORD inputRecord;

    while (1) {
        if (!ReadConsoleInput(hConsole, &inputRecord, 1, &numRead)) {
            fprintf(stderr, "Error: failed to read console input\n");
            continue;
        }

        if (inputRecord.EventType == WINDOW_BUFFER_SIZE_EVENT) {
            system("cls");
            get_scr_size();
            print_frame();
        }
    }
    CloseHandle(hConsole);
}

void get_scr_size()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: failed to get console handle\n");
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        fprintf(stderr, "Error: failed to get console buffer info\n");
        return;
    }

    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void print_frame()
{
    if ((width < MIN_WIDTH || height < MIN_HEIGHT) || (width > MAX_WIDTH || height > MAX_HEIGHT)) {
        fprintf(stderr, "Increase the terminal size\n");
        return;
    }

    size_t bufferSize = (width * height) * 3;
    char *buffer = malloc(bufferSize);
    if (!buffer) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        return;
    }

    u_short index = 0;

    // Horizontal borders
    for (u_short x = 1; x < width; ++x) {
        index += sprintf(buffer + index, "\e[3;%dH-", x);
    }

    // Vertical borders
    for (u_short y = 2; y < height + 1; ++y) {
        index += sprintf(buffer + index, "\e[%d;1H│", y);         // Left
        index += sprintf(buffer + index, "\e[%d;%dH│", y, width); // Right
    }

    // Title and command borders
    for (u_short x = 2; x < width; ++x) {
        index += sprintf(buffer + index, "\e[1;%dH_", x);              //Titles
        index += sprintf(buffer + index, "\e[%d;%dH_", height - 1, x); //Commands
    }

    // Middle separate line
    u_short mid = width / 2;
    for (u_short y = 2; y < height; ++y) {
        index += sprintf(buffer + index, "\e[%d;%dH│", y, mid);
    }

    // Titles
    index += sprintf(buffer + index, "\e[2;%dHCatalog", (mid / 2) - 3);
    index += sprintf(buffer + index, "\e[2;%dHContent", (mid + (mid / 2)) - 3);

    // Buffer output
    printf("%s", buffer);
    free(buffer);
}