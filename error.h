#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define exit_faile_with_msg(msg) \
do { \
    print_error(__FILE__, __LINE__, __func__, msg); \
    exit(EXIT_FAILURE); \
} while(0);


void print_error(const char *filename, int line, const char *funcname, const char *msg);

void print_error(const char *filename, int line, const char *funcname, const char *msg) {
    fprintf(stderr, "%s:%d at %s\n\tmessage:%s\n", filename, line, funcname, msg);
    return;
}

#endif