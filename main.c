#include <stdio.h>
#include "string.h"
#include "error.h"

int main(void) {
    string hello = string_format("%s%S%%\n", "hello, ", string_from_literal("world!"));
    printf("%s", hello.ptr);
    return 0;
}