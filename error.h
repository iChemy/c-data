#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Macro for exiting the program with an error message.
 * @param msg The error message to be printed.
*/
#define exit_faile_with_msg(msg) \
do { \
    print_error(__FILE__, __LINE__, __func__, msg); \
    exit(EXIT_FAILURE); \
} while(0);

void print_error(const char *filename, int line, const char *funcname, const char *msg);

/**
 * @brief Function to print an error message to stderr.
 * @param filename The name of the file where the error occurred.
 * @param line The line number in the file where the error occurred.
 * @param funcname The name of the function where the error occurred.
 * @param msg The error message to be printed.
*/
void print_error(const char *filename, int line, const char *funcname, const char *msg) {
    fprintf(stderr, "%s:%d at %s\n\tmessage:%s\n", filename, line, funcname, msg);
    return;
}

#endif