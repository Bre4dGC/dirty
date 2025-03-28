#ifndef JSON_H
#define JSON_H

#include <stdio.h>
#include <stdlib.h>
#include "cjson/cJSON.h"
#include "utils/config.h"

char* hex_converter(int color);                // Convert color from int to HEX string
cJSON* json_serialize(const config_t *config); // Function for creating JSON object from config_t

#endif // JSON_H