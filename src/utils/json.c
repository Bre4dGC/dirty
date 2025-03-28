#include <json.h>

// Convert color from int to HEX string
char* hex_converter(int color) {
    char *hex = malloc(8); // Allocate memory for HEX string (RRRGGBB\0)
    sprintf(hex, "%06X", color); // Convert int to HEX
    return hex;
}

// Function for creating JSON object from config_t
cJSON* json_serialize(const config_t *config) {
    cJSON *root = cJSON_CreateObject(); // Root JSON object

    // Add simple fields
    cJSON_AddStringToObject(root, "font", config->font);
    cJSON_AddStringToObject(root, "current_theme", config->curr_theme);
    cJSON_AddStringToObject(root, "home_path", config->home_path);

    cJSON *themes_array = cJSON_CreateArray(); // Array for themes

    for (int i = 0; i < config->themes_count; i++) {
        cJSON *theme_obj = cJSON_CreateObject(); // Theme object

        // Add theme fields
        cJSON_AddStringToObject(theme_obj, "name", config->themes[i].name);
        cJSON_AddStringToObject(theme_obj, "bg_color", hex_converter(config->themes[i].bg_color));
        cJSON_AddStringToObject(theme_obj, "fg_color", hex_converter(config->themes[i].fg_color));
        cJSON_AddStringToObject(theme_obj, "hl_color", hex_converter(config->themes[i].hl_color));
        cJSON_AddItemToArray(themes_array, theme_obj);
    }
    cJSON_AddItemToObject(root, "themes", themes_array); // Add themes array to root

    cJSON *hotkeys_array = cJSON_CreateArray(); // Array for hotkeys

    // Add hotkeys
    for (int i = 0; i < config->hotkeys_count; i++) {
        cJSON *hotkey_obj = cJSON_CreateObject(); // Hotkey object
        
        // Add hotkey fields
        cJSON_AddStringToObject(hotkey_obj, "keys", config->hotkeys[i].keys);
        cJSON_AddStringToObject(hotkey_obj, "action", "open_file"); // TODO: add logic to define the function name
        cJSON_AddItemToArray(hotkeys_array, hotkey_obj);
    }
    cJSON_AddItemToObject(root, "hotkeys", hotkeys_array); // Add hotkeys array to root
    return root;
}

    // Example of usage //
/* 
 * theme_t themes[] = {
 *     {"Dark", 0x000000, 0xFFFFFF, 0xFFFFFF}
 * };
 * hotkey_t hotkeys[] = {
 *     {"Ctrl+O", NULL} // we leave action NULL, because it cannot be serialized directly
 * };
 * config_t config = {
 *     "Consolas",
 *     "Dark",
 *     "C/Users/username/Documents/",
 *     themes,
 *     1, // Themes count
 *     hotkeys,
 *     1  // Hotkeys count
 * };
 * 
 * // Convert config_t to JSON
 * cJSON *json = json_serialize(&config);
 * char *json_string = cJSON_Print(json);
 * printf("JSON:\n%s\n", json_string);
 * 
 * // Releasing the memory
 * cJSON_Delete(json);
 * free(json_string);
 */