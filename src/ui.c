#include "../include/ui.h"

// void init_ui() {
//         initscr();  // Инициализация ncurses
//         noecho();    // Не отображать вводимые символы
//         curs_set(0); // Скрыть курсор
//         keypad(stdscr, TRUE); // Включить поддержку клавиш

//         start_color();
//         init_pair(1, COLOR_WHITE, COLOR_BLACK);
//         init_pair(2, COLOR_YELLOW, COLOR_BLACK);

//         // Создание окон
//         WINDOW *left_panel = newwin(LINES - 2, COLS / 2, 0, 0);
//         WINDOW *right_panel = newwin(LINES - 2, COLS / 2, 0, COLS / 2);
//         WINDOW *command_line = newwin(2, COLS, LINES - 2, 0);

//         wbkgd(left_panel, COLOR_PAIR(1));
//         wbkgd(right_panel, COLOR_PAIR(2));
//         wbkgd(command_line, COLOR_PAIR(1));

//         box(left_panel, 0, 0);
//         box(right_panel, 0, 0);
//         box(command_line, 0, 0);

//         wrefresh(left_panel);
//         wrefresh(right_panel);
//         wrefresh(command_line);
// }

// int main() {
//         init_ui();

//         getch(); // Ожидание нажатия клавиши перед выходом
//         endwin();
//         return 0;
// }

//#pragma once
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include <string.h>
//#include <wchar.h>
//#include <locale.h>
//#include <PDcurses/curses.h>
//
//#define MIN_WIDTH  32
//#define MIN_HEIGHT 16
//#define MAX_WIDTH  200
//#define MAX_HEIGHT 100
//#define INITIAL_ROWS 10  // Начальное количество строк
//#define MAX_NAME_LEN 128 // Длина имени файла
//#define LINE_LEN     40  // Ширина отображаемой строки
//#define HEIGHT       40  // Ширина отображаемой строки
//
//wchar_t *path = L"C:\\*";
//wchar_t **files = NULL;
//u_short selected_index = 0;
//u_short start = 0, end = 0;
//u_short count = 0;
//
//void get_scr_size();
//void draw_border(WINDOW *win);
//void handle_resize(WINDOW *win);
//
//void draw_menu();
//void get_catalog();
//void handle_input();
//void update_selection(u_short old_index, u_short new_index);
//wchar_t* str_cut(const wchar_t* str);
//
//u_short width = 0, height = 0; // Screen size
//
//int main()
//{
//    initscr();
//    cbreak();
//    noecho();
//    curs_set(0);
//
//    setlocale(LC_ALL, "");
//    SetConsoleOutputCP(CP_UTF8);
//    system("chcp 850");
//
//    get_scr_size(); // Получаем размер окна
//
//    // Создаем окно с текущими размерами
//    WINDOW *win = newwin(height, width, 0, 0);
//    draw_border(win);       // Печатаем рамку
//    handle_resize(win);     // Начинаем обработку событий изменения размера
//
//    endwin();
//
//
//    // get_catalog();
//    // draw_menu();
//    // handle_input();
//
//    // for (u_short i = 0; i < count; i++) {
//    //     free(files[i]); // Освобождаем память для каждого имени файла
//    // }
//    // free(files); // Освобождаем массив указателей
//    return 0;
//}
//
//void handle_resize(WINDOW *win) {
//    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
//    if (hConsole == INVALID_HANDLE_VALUE) {
//        fprintf(stderr, "Error: failed to get console handle\n");
//        return;
//    }
//
//    DWORD numRead;
//    INPUT_RECORD inputRecord;
//
//    while (1) {
//        if (!ReadConsoleInput(hConsole, &inputRecord, 1, &numRead)) {
//            fprintf(stderr, "Error: failed to read console input\n");
//            continue;
//        }
//
//        if (inputRecord.EventType == WINDOW_BUFFER_SIZE_EVENT) {
//            get_scr_size(); // Получаем размер окна
//
//            // Проверяем, не выходят ли размеры за допустимые пределы
//            if ((width < MIN_WIDTH || height < MIN_HEIGHT) ||
//                (width > MAX_WIDTH || height > MAX_HEIGHT)) {
//                fprintf(stderr, "Increase the terminal size\n");
//                continue;
//            }
//
//            // Пересоздаём окно с новыми размерами
//            wresize(win, height, width);
//            draw_border(win); // Печатаем рамку для нового размера
//        }
//    }
//
//    CloseHandle(hConsole);
//}
//
//void get_scr_size()
//{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (hConsole == INVALID_HANDLE_VALUE) {
//        fprintf(stderr, "Error: failed to get console handle\n");
//        return;
//    }
//
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
//        fprintf(stderr, "Error: failed to get console buffer info\n");
//        return;
//    }
//
//    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
//}
//
//void draw_border(WINDOW *win) {
//    clear();
//    wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
//            ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
//    wrefresh(win);  // Обновляем окно
//}
//
//
//
//
//
//
//
//
//
//
//
//
//void draw_menu() {
//    for (u_short i = 0; i < count; i++) {
//        printf("\033[%d;1H", i + 1);
//        if (i == selected_index) {
//            printf(">");
//            if (wcslen(files[i]) < LINE_LEN) {
//                wprintf(L"%s", files[i]);
//            }
//            else {
//                wchar_t* cut_str = str_cut(files[i]);
//                wprintf(L" %s", cut_str);
//                free(cut_str); // Освобождаем память после использования
//            }
//            u_short fname_len = wcslen(files[i]);
//            for (u_short j = 0; j < (LINE_LEN - fname_len); j++) {
//                printf("=");
//            }
//        } else {
//            if (wcslen(files[i]) < LINE_LEN) {
//                wprintf(L" %s", files[i]);
//            } else {
//                wchar_t *cut_str = str_cut(files[i]);
//                wprintf(L" %s", cut_str);
//                free(cut_str); // Освобождаем память после использования
//            }
//        }
//        printf("\n");
//    }
//}
//
//// Обновляем только изменённые строки
//void update_selection(u_short old_index, u_short new_index) {
//    printf("\033[%d;1H ", old_index + 1);
//    wprintf(L"%s\033[K", files[old_index]);
//
//    printf("\033[%d;1H>", new_index + 1);
//    wprintf(L"%s", files[new_index]);
//
//    u_short fname_len = wcslen(files[new_index]);
//    for (u_short j = 0; j < (LINE_LEN - fname_len); j++) {
//        printf("=");
//    }
//    printf("\033[K"); // Очищаем остатки строки
//}
//
//// Функция обработки ввода
//void handle_input() {
//    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
//    DWORD numRead;
//    INPUT_RECORD inputRecord;
//
//    while (1) {
//        ReadConsoleInput(hConsole, &inputRecord, 1, &numRead);
//        if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
//            u_short old_index = selected_index;
//            switch (inputRecord.Event.KeyEvent.wVirtualKeyCode) {
//                case VK_UP:
//                    if (selected_index > 0) selected_index--;
//                    break;
//                case VK_DOWN:
//                    if (selected_index < count - 1) selected_index++;
//                    break;
//                case VK_RETURN:
//                    return;
//            }
//            if (old_index != selected_index) {
//                update_selection(old_index, selected_index);
//            }
//        }
//    }
//}
//
//void get_catalog()
//{
//    u_short capacity = INITIAL_ROWS;
//    files = malloc(capacity * sizeof(wchar_t*));
//    if (!files) {
//        fprintf(stderr, "Ошибка: не удалось выделить память для списка файлов\n");
//        return;
//    }
//
//    WIN32_FIND_DATAW findData;
//    HANDLE hFind = FindFirstFileW(path, &findData);
//
//    if (hFind == INVALID_HANDLE_VALUE) {
//        fprintf(stderr, "Ошибка: не удалось открыть каталог\n");
//        free(files);
//        return;
//    }
//
//    do {
//        if (count >= capacity) {
//            capacity *= 2;
//            wchar_t **temp = realloc(files, sizeof(wchar_t*) * capacity);
//            if (!temp) {
//                fprintf(stderr, "Ошибка: не удалось перевыделить память\n");
//                FindClose(hFind);
//                return;
//            }
//            files = temp;
//        }
//
//        files[count] = malloc((MAX_NAME_LEN + 1) * sizeof(wchar_t));
//        if (!files[count]) {
//            fprintf(stderr, "Ошибка: не удалось выделить память для имени файла\n");
//            break;
//        }
//        wcsncpy(files[count], findData.cFileName, MAX_NAME_LEN);
//        files[count][MAX_NAME_LEN] = L'\0';
//
//        count++;
//    } while (FindNextFileW(hFind, &findData));
//
//    FindClose(hFind);
//}
//
//// Функция обрезки строки с возвратом нового выделенного массива
//wchar_t* str_cut(const wchar_t* str) {
//    u_short max_display_len = LINE_LEN - 3; // Учитываем ".."
//
//    // Если длина строки меньше допустимой, возвращаем копию без изменений
//    u_short len = wcslen(str);
//    if (len <= max_display_len) {
//        return _wcsdup(str); // Выделяем копию строки
//    }
//
//    // Выделяем память для укороченной строки
//    wchar_t* cut = malloc((max_display_len + 3) * sizeof(wchar_t)); // +3 для ".." и '\0'
//    if (!cut) return NULL; // Проверяем выделение памяти
//
//    // Копируем первые max_display_len символов
//    wcsncpy(cut, str, max_display_len);
//    cut[max_display_len] = L'\0'; // Завершаем строку
//
//    // Добавляем ".." в конец
//    wcscat(cut, L"..");
//
//    return cut; // Вернём обрезанную строку
//}