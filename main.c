#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void get_scr_size();
void print_frame();
void event_loop();

u_short width = 0, height = 0; // Screen size

int main()
{
  system("cls");
  printf("\e[?25l"); // Turn off the caret

  get_scr_size(); // Get size of screen
  print_frame();  // Printing frame
  event_loop();   // Start of events handling
  return 0;
}

void event_loop() {
  HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
  DWORD numRead;
  INPUT_RECORD inputRecord;

  while (1) {
    ReadConsoleInput(hConsole, &inputRecord, 1, &numRead);

    if (inputRecord.EventType == WINDOW_BUFFER_SIZE_EVENT) {
      system("cls");
      print_frame();
    }
  }
}

void get_scr_size()
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  } else {
    printf("Error: failed to get console size\n");
  }
}

void print_frame()
{
  get_scr_size(); // Get size of screen

  if (height < 7) return;

  char buffer[(width * height) * 2];
  u_short index = 0;

  for(u_short x = 2; x < width; ++x) {
    index += sprintf(buffer + index, "\e[1;%dH_\e[%d;%dH_", x, height-1, x);
  }

  for(u_short x = 1; x < width; ++x){
    index += sprintf(buffer + index, "\e[%d;%dH-", 3, x);
  }

  for(u_short y = 2; y < height+1; ++y) {
    index += sprintf(buffer + index, "\e[%d;1H|\e[%d;%dH|", y, y, width);
  }

  u_short mid = width / 2;
  for (u_short y = 2; y < height; ++y){
    index += sprintf(buffer + index, "\e[%d;%dH|", y, mid);
  }

  printf("%s", buffer);
  printf("\e[2;%dHCatalog\e[2;%dHContent", (mid / 2)-3, (mid + (mid/2))-3);
}

void get_catalog(char *path, char *names)
{
  strcat(path,"/*");

  u_short len = 0;

  WIN32_FIND_DATA f;
  HANDLE h = FindFirstFile(path, &f);

  if(h != INVALID_HANDLE_VALUE){
    while(FindNextFile(h, &f)) {
      names = realloc(names, sizeof(f.cFileName));
      strcat(names, f.cFileName);
      len++;
    }
  }
  else {
    fprintf(stderr, "Error opening directory\n");
  }
  puts(names);

}