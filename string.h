#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include "error.h"

#define STRING_INIT_CAP 128
#define STRING_INC_CAP 128

/// @brief 
typedef struct string
{
    /// @brief 
    unsigned int len;
    /// @brief 
    unsigned int cap;
    /// @brief 
    char *ptr;
} string;

typedef string freed_string;

string string_new();
void string_free(string *str);
void string_push_char(string *str, char c);
string string_from_literal(const char *literal);

/// @brief 
/// @return 
string string_new() {
    string res = {0, STRING_INIT_CAP, NULL};
    if ((res.ptr = (char *)malloc(sizeof(char) * STRING_INIT_CAP)) == NULL) {
        exit_faile_with_msg("ERROR: Failed to allocate memory to string");
    }
    return res;
}

/// @brief 
/// @param str 
void string_free(string *str) {
    free(str->ptr);
    *str = (freed_string)*str;
}

/// @brief 
/// @param str 
/// @param c 
void string_push_char(string *str, char c) {
    char *np = NULL;
    str->len++;
    if (str->len >= str->cap) {
        if ((np = (char *)realloc(str->ptr, sizeof(char)*(str->cap + STRING_INC_CAP))) == NULL) {
            exit_faile_with_msg("ERROR: Failed to reallocate memory to string");
        }
        str->ptr = np;
    }
    str->ptr[str->len - 1] = c;
    str->ptr[str->len] = '\0';
    return;
}

/// @brief 
/// @param literal 
/// @return 
string string_from_literal(const char *literal) {
    string res = string_new();
    while (*literal)
    {
        string_push_char(&res, *literal);
        literal++;
    }
    return res;
}



#endif