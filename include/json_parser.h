// json_parser.h
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Типы JSON значений
typedef enum {
    JSON_NULL,
    JSON_BOOL,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT
} JsonType;

// Структура для представления пары ключ-значение
typedef struct JsonPair {
    char* key;
    struct JsonValue* value;
    struct JsonPair* next;
} JsonPair;

// Структура для представления элемента массива
typedef struct JsonElement {
    struct JsonValue* value;
    struct JsonElement* next;
} JsonElement;

// Структура для представления JSON значения
typedef struct JsonValue {
    JsonType type;
    union {
        int boolean;
        double number;
        char* string;
        JsonElement* array;
        JsonPair* object;
    } data;
} JsonValue;

// Функции для парсинга
JsonValue* parseJson(const char* json);
void freeJsonValue(JsonValue* value);
const char* skipWhitespace(const char* json);
JsonValue* parseValue(const char** json);

// Вспомогательные функции для извлечения данных
const char* jsonGetString(JsonValue* value, const char* key);
double jsonGetNumber(JsonValue* value, const char* key);
int jsonGetBool(JsonValue* value, const char* key);
JsonValue* jsonGetObject(JsonValue* value, const char* key);
JsonValue* jsonGetArray(JsonValue* value, const char* key);
JsonValue* jsonGetArrayElement(JsonValue* array, int index);

#endif // JSON_PARSER_H