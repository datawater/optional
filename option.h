/*

* Copyright 2023 datawater <datawater1@gmail.com>
 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
* and associated documentation files (the “Software”), to deal in the Software without restriction, 
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
* subject to the following conditions:
 
* The above copyright notice and this permission notice shall be included in all copies
* or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wint-conversion"
#endif

#ifdef __clang__
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#pragma clang diagnostic ignored "-Wint-conversion"
#endif

#define None NULL

// typedef enum {
//     BOOL,
//     INT,
//     UINT,
//     U8,
//     U16,
//     U32,
//     U64,
//     I8,
//     I16,
//     I32,
//     I64,
//     SIZET,
//     SSIZET
// } types_h;

struct Option_ {
    void* some;
};

typedef struct Option_ Option;

struct Option_h_ {
    Option (*new_option)(void*);
    void* (*unwrap)(Option*);
    void* (*unwrap_or)(Option*, void*);
    void* (*unwrap_or_else)(Option*, void* (*closure)(void*));
    bool (*is_none)(Option*);
    bool (*is_some)(Option*);
    bool (*is_some_and)(Option*, void*);
};

typedef struct Option_h_ Option_h;

#ifdef OPTION_IMPLEMENTATION

Option __new__option__(void* value) {
    return (Option) {value};
}

void* __unwrap__(Option* option) {
    if (option->some == NULL) {
        fprintf(stderr, "\n--- --- --- ---\nPANIC. CALLED UNWRAP ON NONE\n--- --- --- ---\n");
        exit(1);
    }

    return option->some;
}

void* __unwrap_or__(Option* option, void* or) {
    return option->some == NULL ? or : option->some;
}

void* __unwrap_or_else__(Option* option, void* (*closure)(void*)) {
    void* to_return = closure(option->some);
    
    if (option->some == NULL || to_return == NULL) {
        fprintf(stderr, "PANIC. CALLED UNWRAP ON NONE\n");
        exit(1);
    }

    return to_return;
}

bool __is_none__(Option* option) {
    return option->some == NULL;
}

bool __is_some__(Option* option) {
    return option->some != NULL;
}

bool __is_some_and__(Option* option, void* and) {
    return option->some != NULL && option->some == and;
}

Option_h new_option_h() {
    return (Option_h) {
        &__new__option__,
        &__unwrap__,
        &__unwrap_or__,
        &__unwrap_or_else__,
        &__is_none__,
        &__is_some__,
        &__is_some_and__,
    };
}

#endif // OPTION_IMPLEMENTATION