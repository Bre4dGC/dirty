#include <stdio.h>
#include "operations.h"
#include "ui.h"
#include "config.h"

int main()
{
    // Загрузка конфигурации
    config_t *config = load_config("config.json");
    if (!config) {
        fprintf(stderr, "Failed to load configuration\n");
        return 1;
    }
    
    // Инициализация UI
    init_ui();
    
    // Основной цикл программы
    int ch;
    while ((ch = getch()) != 'q') {
        navigate(ch);
    }
    
    // Очистка ресурсов
    cleanup_ui();
    free_config(config);
    
    return 0;    
}