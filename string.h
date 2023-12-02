#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdarg.h>
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
void string_push_literal(string *str, const char *literal);
void string_push_string(string *str, string pushed_str);
string string_from_literal(const char *literal);
string string_format(const char *format, ...);

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
/// @param str 
/// @param literal 
void string_push_literal(string *str, const char *literal) {
    while (*literal)
    {
        string_push_char(str, *literal);
        literal++;
    }
}

/// @brief 
/// @param str 
/// @param pushed_str 
void string_push_string(string *str, string pushed_str) {
    string_push_literal(str, pushed_str.ptr);
}

/// @brief 
/// @param literal 
/// @return 
string string_from_literal(const char *literal) {
    string res = string_new();
    string_push_literal(&res, literal);
    return res;
}

/// @brief 
/// @param format 
/// @param  
/// @return 
string string_format(const char *format, ...) {
    string res = string_new();
    unsigned char format_specifier_flag = 0;
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (format_specifier_flag == 0) {
            if (*format == '%') {
                format_specifier_flag = 1;
            } else {
                string_push_char(&res, *format);
            }
        } else {
            if (*format == '%') {
                string_push_char(&res, '%');
            } else if (*format == 's') {
                char *l_arg = va_arg(args, char*);
                string_push_literal(&res, l_arg);
            } else if (*format == 'S') {
                string s_arg = va_arg(args, string);
                string_push_string(&res, s_arg);
            }
            format_specifier_flag = 0;
        }
        format++;
    }
    return res;
}



#endif