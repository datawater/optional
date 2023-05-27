# Optional - options in c

## Why

Idk, I got bored.

## How

`void*`

## Documentation

Optional is a [STB style library](https://github.com/nothings/stb). If you want to also you the implementation part, you have to define the header `OPTION_IMPLEMENTATION` before including "option.h"

```c
#define OPTION_IMPLEMENTATION
#include "option.h"

int main(int argc, char** argv) {
    ...
}
```

The library depends on a struct full of function pointers, to emulate a class and call functions in a dot notation format. You have to call `new_option_h` to get the said struct.

```c
#define OPTION_IMPLEMENTATION
#include "option.h"

int main(int argc, char** argv) {
    Option_h option_h = new_option_h();
    
    ...
}
```

And I'm too lazy to write the documentations of functions (for now), so look in the [example.c](./example.c) file, and you'll get the jist of it.

## Legal stuff

The library is released under MIT

[LICENSE](./LICENSE)