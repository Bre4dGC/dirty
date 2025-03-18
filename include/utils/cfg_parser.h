#include "config.h"

typedef enum {
    VAL_NULL,
    VAL_BOOL,
    VAL_NUMBER,
    VAL_STRING,
    VAL_ARRAY,
    VAL_OBJECT
} Type;

// key-value pair representation
typedef struct {
    char *key;
    Value *value;
    Pair *next;
} Pair;

// Array element representation
typedef struct {
    Value *value;
    Element *next;
} Element;

// JSON value representation
typedef struct {
    Type type;
    union {
        int boolean;
        double number;
        char *string;
        Element *array;
        Pair *object;
    } data;
} Value;

Value *parse();
void change_data();
void save_changes();