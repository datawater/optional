#include <stdio.h>

#define OPTION_IMPLEMENTATION
#include "option.h"

#include <assert.h>

void* or_else(void* value) {
    return -((int) value) * 256;
}

void println_bool(bool value) {
    printf("%s\n", value == true ? "true" : "false");
}

int main(void) {
    Option_h option_h = new_option_h();

    Option optional_none = option_h.new_option(None);
    Option optional_some = option_h.new_option(256);

    assert(option_h.is_some(&optional_some));

    printf("%d\n", (int) option_h.unwrap(&optional_some));
    printf("%d\n", (int) option_h.unwrap_or_else(&optional_some, &or_else));
    printf("%s\n", (char*) option_h.unwrap_or(&optional_none, (void*) "or None :("));
    
    println_bool(option_h.is_none(&optional_none));
    println_bool(option_h.is_some(&optional_some));
    println_bool(option_h.is_some_and(&optional_some, 256));
    println_bool(option_h.is_some_and(&optional_some, 512));

    option_h.unwrap(&optional_none);
    return 0;
}