// json_parser.c
#include "json_parser.h"

// Парсинг JSON строки
JsonValue* parseJson(const char* json) {
    json = skipWhitespace(json);
    return parseValue(&json);
}

// Пропуск пробелов и табуляций
const char* skipWhitespace(const char *json) {
    while (*json && isspace(*json)) {
        json++;
    }
    return json;
}

// Парсинг JSON значения
JsonValue* parseValue(const char **json) {
    *json = skipWhitespace(*json);
    
    JsonValue* value = (JsonValue *)malloc(sizeof(JsonValue));
    if (!value) return NULL;
    
    // Определяем тип значения по первому символу
    switch (**json) {
        case 'n': // null
            if (strncmp(*json, "null", 4) == 0) {
                value->type = JSON_NULL;
                *json += 4;
            }
            break;
            
        case 't': // true
            if (strncmp(*json, "true", 4) == 0) {
                value->type = JSON_BOOL;
                value->data.boolean = 1;
                *json += 4;
            }
            break;
            
        case 'f': // false
            if (strncmp(*json, "false", 5) == 0) {
                value->type = JSON_BOOL;
                value->data.boolean = 0;
                *json += 5;
            }
            break;
            
        case '"': { // string
            value->type = JSON_STRING;
            (*json)++; // Пропускаем открывающую кавычку
            
            const char* start = *json;
            while (**json && **json != '"') {
                // Обработка экранированных символов
                if (**json == '\\' && *(*json + 1)) {
                    (*json)++;
                }
                (*json)++;
            }
            
            int len = *json - start;
            value->data.string = (char *)malloc(len + 1);
            if (value->data.string) {
                strncpy(value->data.string, start, len);
                value->data.string[len] = '\0';
            }
            
            if (**json == '"') (*json)++; // Пропускаем закрывающую кавычку
            break;
        }
            
        case '{': { // object
            value->type = JSON_OBJECT;
            value->data.object = NULL;
            (*json)++; // Пропускаем '{'
            
            *json = skipWhitespace(*json);
            if (**json == '}') {
                (*json)++; // Пустой объект
                break;
            }
            
            JsonPair* lastPair = NULL;
            
            do {
                *json = skipWhitespace(*json);
                if (**json != '"') break; // Ожидаем ключ (строку)
                
                // Парсим ключ
                const char* keyStart = ++(*json);
                while (**json && **json != '"') {
                    if (**json == '\\' && *(*json + 1)) {
                        (*json)++;
                    }
                    (*json)++;
                }
                
                int keyLen = *json - keyStart;
                char* key = (char*)malloc(keyLen + 1);
                if (key) {
                    strncpy(key, keyStart, keyLen);
                    key[keyLen] = '\0';
                }
                
                if (**json == '"') (*json)++;
                
                *json = skipWhitespace(*json);
                if (**json != ':') {
                    free(key);
                    break; // Ожидаем двоеточие после ключа
                }
                
                (*json)++; // Пропускаем ':'
                
                // Парсим значение
                JsonValue *pairValue = parseValue(json);
                
                // Создаем новую пару ключ-значение
                JsonPair *pair = (JsonPair *)malloc(sizeof(JsonPair));
                if (pair) {
                    pair->key = key;
                    pair->value = pairValue;
                    pair->next = NULL;
                    
                    if (lastPair) {
                        lastPair->next = pair;
                    } else {
                        value->data.object = pair;
                    }
                    
                    lastPair = pair;
                }
                
                *json = skipWhitespace(*json);
            } while (**json == ',' && ((*json)++, 1));
            
            if (**json == '}') (*json)++;
            break;
        }
            
        case '[': { // array
            value->type = JSON_ARRAY;
            value->data.array = NULL;
            (*json)++; // Пропускаем '['
            
            *json = skipWhitespace(*json);
            if (**json == ']') {
                (*json)++; // Пустой массив
                break;
            }
            
            JsonElement* lastElement = NULL;
            
            do {
                // Парсим элемент массива
                JsonValue *elementValue = parseValue(json);
                
                // Создаем новый элемент массива
                JsonElement *element = (JsonElement *)malloc(sizeof(JsonElement));
                if (element) {
                    element->value = elementValue;
                    element->next = NULL;
                    
                    if (lastElement) {
                        lastElement->next = element;
                    } else {
                        value->data.array = element;
                    }
                    
                    lastElement = element;
                }
                
                *json = skipWhitespace(*json);
            } while (**json == ',' && ((*json)++, 1));
            
            if (**json == ']') (*json)++;
            break;
        }
            
        default: // number
            if (isdigit(**json) || **json == '-') {
                value->type = JSON_NUMBER;
                char* end;
                value->data.number = strtod(*json, &end);
                *json = end;
            }
            break;
    }
    return value;
}

// Освобождение памяти
void freeJsonValue(JsonValue *value) {
    if (!value) return;
    
    switch (value->type) {
        case JSON_STRING:
            free(value->data.string);
            break;
            
        case JSON_ARRAY: {
            JsonElement *element = value->data.array;
            while (element) {
                JsonElement *next = element->next;
                freeJsonValue(element->value);
                free(element);
                element = next;
            }
            break;
        }
            
        case JSON_OBJECT: {
            JsonPair *pair = value->data.object;
            while (pair) {
                JsonPair* next = pair->next;
                free(pair->key);
                freeJsonValue(pair->value);
                free(pair);
                pair = next;
            }
            break;
        }
            
        default:
            break;
    }
    
    free(value);
}

// Вспомогательные функции для работы с JSON
const char* jsonGetString(JsonValue *value, const char *key) {
    if (!value || value->type != JSON_OBJECT) return NULL;
    
    JsonPair* pair = value->data.object;
    while (pair) {
        if (strcmp(pair->key, key) == 0 && pair->value->type == JSON_STRING) {
            return pair->value->data.string;
        }
        pair = pair->next;
    }
    
    return NULL;
}

double jsonGetNumber(JsonValue *value, const char *key) {
    if (!value || value->type != JSON_OBJECT) return 0;
    
    JsonPair* pair = value->data.object;
    while (pair) {
        if (strcmp(pair->key, key) == 0 && pair->value->type == JSON_NUMBER) {
            return pair->value->data.number;
        }
        pair = pair->next;
    }
    
    return 0;
}

int jsonGetBool(JsonValue *value, const char *key) {
    if (!value || value->type != JSON_OBJECT) return 0;
    
    JsonPair *pair = value->data.object;
    while (pair) {
        if (strcmp(pair->key, key) == 0 && pair->value->type == JSON_BOOL) {
            return pair->value->data.boolean;
        }
        pair = pair->next;
    }
    
    return 0;
}

JsonValue* jsonGetObject(JsonValue *value, const char *key) {
    if (!value || value->type != JSON_OBJECT) return NULL;
    
    JsonPair *pair = value->data.object;
    while (pair) {
        if (strcmp(pair->key, key) == 0 && pair->value->type == JSON_OBJECT) {
            return pair->value;
        }
        pair = pair->next;
    }
    
    return NULL;
}

JsonValue* jsonGetArray(JsonValue *value, const char *key) {
    if (!value || value->type != JSON_OBJECT) return NULL;
    
    JsonPair *pair = value->data.object;
    while (pair) {
        if (strcmp(pair->key, key) == 0 && pair->value->type == JSON_ARRAY) {
            return pair->value;
        }
        pair = pair->next;
    }
    
    return NULL;
}

JsonValue* jsonGetArrayElement(JsonValue *array, int index) {
    if (!array || array->type != JSON_ARRAY) return NULL;
    
    JsonElement *element = array->data.array;
    for (int i = 0; i < index && element; i++) {
        element = element->next;
    }
    
    return element ? element->value : NULL;
}