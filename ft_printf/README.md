*This project has been created as part of the 42 curriculum by aantela-*

# ft_printf

## Description

`ft_printf` is a recreation of the standard C `printf()` function from the C standard library.

The purpose of this project is to understand and implement variadic functions in C using `va_list`, `va_start`, `va_arg`, and `va_end`.

The implementation reproduces the behavior of `printf()` for the mandatory conversions required by the project:

* `%c` → prints a character
* `%s` → prints a string
* `%p` → prints a pointer address in hexadecimal
* `%d` → prints a decimal integer
* `%i` → prints an integer
* `%u` → prints an unsigned integer
* `%x` → prints a hexadecimal number (lowercase)
* `%X` → prints a hexadecimal number (uppercase)
* `%%` → prints a percent sign

The project was developed according to the 42 Norm and compiled using:

```bash
-Wall -Wextra -Werror
```

---

## Instructions

### Clone the repository

```bash
git clone https://github.com/ArturVazOsorio/42-ft_printf
cd ft_printf
```

### Compile

```bash
make
```

This generates:

```bash
libftprintf.a
```

### Clean object files

```bash
make clean
```

### Remove object files and library

```bash
make fclean
```

### Rebuild everything

```bash
make re
```

---

## Usage

Include the header:

```c
#include "ft_printf.h"
```

Example:

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s!\n", "World");
    ft_printf("Number: %d\n", 42);
    ft_printf("Hex: %x\n", 255);

    return (0);
}
```

Compile with:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -o program
```

Run:

```bash
./program
```

---

## Technical Choices

The implementation is divided into smaller helper functions.

The main `ft_printf()` function scans the format string character by character.

When a `%` symbol is found:

1. The next character is analyzed.
2. A dedicated helper function selects the corresponding conversion.
3. The argument is extracted using `va_arg`.
4. The selected printing function handles formatting and output.
5. The number of written characters is returned and accumulated.

Hexadecimal and numeric outputs are implemented recursively.

Example:

```text
255
 └─ 255 / 16 = 15
      └─ 15 -> 'f'
 └─ 255 % 16 = 15 -> 'f'

Output: ff
```

This approach provides:

* modularity
* easier debugging
* cleaner code
* easier future extension for bonuses

---

## Resources

Official documentation:

* https://man7.org/linux/man-pages/man3/printf.3.html
* https://man7.org/linux/man-pages/man3/stdarg.3.html
* https://cplusplus.com/reference/cstdarg/

Learning resources:

* Variadic functions in C
* Recursive number conversion
* Base conversion algorithms

AI usage:

AI was used as a supplementary tool for:

* discussing implementation ideas
* debugging memory issues
* identifying edge cases
* reviewing code structure

All code behavior and implementation decisions were manually tested and validated using:

* custom tests
* Valgrind
* Norminette
* francinette

## Bonus (W I P)

Bonus list:
* • Manage any combination of the following flags: ’-0.’ and the field minimum width under all conversions.
* • Manage all the following flags: ’# +’ (Yes, one of them is a space
