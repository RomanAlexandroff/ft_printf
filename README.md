# FT_PRINTF

*This project has been created as part of the 42 curriculum by roaleksa.*

---

## Table of Contents

- [Project Description](#project-description)
- [Implementation Description](#implementation-description)
- [Makefile Instructions](#makefile-instructions)
- [Library Usage](#library-usage)
- [Project Structure](#project-structure)
- [Supported Format Specifiers](#supported-format-specifiers)
- [Resources](#resources)
- [AI Usage Disclosure](#ai-usage-disclosure)

---

<br>

## Project Description

**ft_printf** is a recreation of the standard C library function `printf()`. The goal of this project within the 42 curriculum is to deepen understanding of formatted output, variadic functions, type conversions, and low-level I/O operations.

The project implements a subset of the standard printf functionality, specifically handling format string parsing and conversion dispatch. It produces a reusable static library that can be linked into other C programs to provide formatted output capabilities comparable to the standard library implementation.

### Scope

This implementation:
- Parses format strings containing conversion specifiers
- Dispatches conversions to specialized output functions
- Supports multiple format specifiers (%c, %s, %p, %d, %i, %u, %x, %X, %%)
- Handles null pointers and null strings with appropriate fallback values
- Returns the total character count written, or a negative value on error
- Uses dynamic memory allocation for number-to-string conversions

---

<br>

## Implementation Description

### Architecture Overview

The implementation follows a modular design with a central dispatcher function that routes format specifiers to specialized output handlers:

1. **Format String Parsing** (`ft_printf.c`)
   - Iterates through the format string character by character
   - Detects '%' followed by a conversion specifier
   - Passes control to the dispatcher for recognized specifiers
   - Writes literal characters directly to standard output

2. **Conversion Dispatching** (`ft_printf.c`)
   - The `dispatcher()` function examines the format specifier
   - Retrieves the next argument from the variadic list using `va_arg()`
   - Calls the appropriate output function based on the specifier
   - Returns character count or error code

### Supported Format Specifiers

| Specifier | Type | Output |
|-----------|------|--------|
| %c | int (char) | Single character |
| %s | char* | Null-terminated string (or "(null)" if pointer is NULL) |
| %p | void* | Pointer address in hexadecimal with "0x" prefix (or "(nil)" if NULL) |
| %d | int | Signed decimal integer |
| %i | int | Signed decimal integer (synonym for %d) |
| %u | unsigned int | Unsigned decimal integer |
| %x | unsigned int | Hexadecimal lowercase (0-9, a-f) |
| %X | unsigned int | Hexadecimal uppercase (0-9, A-F) |
| %% | — | Literal '%' character |

### Output Functions

**Character and String Output** (`put_char_str.c`)
- `ft_putchar(int c)`: Writes a single character via `write()`
- `ft_putstr(char *str)`: Writes a null-terminated string character by character

**Pointer and Hexadecimal Output** (`put_hex_ptr.c`)
- `ft_putptr(uintptr_t ptr, const char format)`: Formats and outputs a pointer address
  - Outputs "(nil)" for NULL pointers
  - Prefixes non-null pointers with "0x"
  - Uses `put_hex()` for the hexadecimal digits
- `ft_puthex(unsigned int num, const char format)`: Formats and outputs hexadecimal integers

**Integer Output** (`put_ints.c`)
- `put_number(long num)`: Converts numbers to strings and outputs them

### Number Conversion and Utilities (`utilities.c`)

- `ft_ltoa(long num)`: Converts a long integer to a dynamically allocated string
  - Handles negative numbers (prefixes with '-')
  - Allocates memory via `malloc()`
  - Returns NULL on allocation failure
- `put_hex(uintptr_t num, const char format)`: Recursively converts and prints hexadecimal values
  - Uses recursion to process digits from most to least significant
  - Supports both lowercase ('x', 'p') and uppercase ('X') formats
- `num_len(long long num, int base)`: Calculates the number of digits required to represent a number in a given base
  - Accounts for the minus sign in negative numbers

### Variadic Arguments Handling

The implementation uses the standard C variadic macro mechanism:
- `va_list`: Maintains state for iterating through arguments
- `va_start(ap, last)`: Initializes the variadic list after the last known parameter
- `va_arg(ap, type)`: Retrieves the next argument of the specified type
- `va_end(ap)`: Cleans up the variadic list

Each format specifier uses the appropriate type with `va_arg()` to retrieve its argument.

### Error Handling

- Returns -1 on write failures (when `write()` returns a negative value)
- Returns -1 if an unrecognized format specifier is encountered
- Memory allocation failure in `ft_ltoa()` propagates as a write error
- Gracefully handles NULL pointers and NULL strings with fallback output

---

<br>

## Makefile Instructions

### Compilation

This project builds a static library using the provided Makefile. The compilation uses the C compiler with strict flags:

```bash
make
```

**Compiler Flags:**
- `-Wall`: Enable most common warnings
- `-Wextra`: Enable additional warnings
- `-Werror`: Treat warnings as errors

### Makefile Targets

| Target | Description | Output |
|--------|-------------|--------|
| `make` or `make all` | Compiles all source files and creates the static library | `libftprintf.a` |
| `make clean` | Removes all compiled object files (`.o`) | — |
| `make fclean` | Removes object files and the static library | — |
| `make re` | Performs `fclean` followed by `all` (full rebuild) | `libftprintf.a` |
| `make norm` | Runs Norminette to check code style compliance | Norminette report |
| `make test` | Compiles and runs the test suite | Test output |
| `make valgrind` or `make leaks` | Runs memory leak detection (uses Valgrind on Linux, Leaks on macOS) | Memory report |
| `make gdb` | Launches the debugger (LLDB on macOS, GDB on Linux) | Debugger session |
| `make git` | Interactively commits and pushes changes | Git output |

### Compilation Details

**Object Files:**
The Makefile compiles the source files into corresponding `.o` object files using the implicit rule `%.o: %.c`.

**Library Creation:**
The `ar rcs` command combines all object files into a static library named `libftprintf.a`.

**Archive Tool:**
- `ar` (archiver) creates and manages static libraries
- `rcs` flags: `r` (replace), `c` (create), `s` (create symbol table)

---

<br>

## Library Usage

### Linking with Your Project

To use `libftprintf.a` in another project:

**1. Copy the library file to your project:**
```bash
cp libftprintf.a /path/to/your/project/
```

**2. Copy the header file:**
```bash
cp ft_printf.h /path/to/your/project/
```

**3. Compile your program with the library:**
```bash
cc -Wall -Wextra -Werror your_program.c -L. -lftprintf -o your_program
```

Alternatively, you can compile directly with the source files:
```bash
cc -Wall -Wextra -Werror your_program.c ft_printf.c put_hex_ptr.c put_char_str.c put_ints.c utilities.c -o your_program
```

### Including the Header

In your source files, include the header:
```c
#include "ft_printf.h"
```

### Function Signature

```c
int ft_printf(const char *format, ...);
```

**Parameters:**
- `format`: A format string containing text and conversion specifiers
- `...`: Variadic arguments matching the specifiers in the format string

**Return Value:**
- Number of characters written on success
- Negative value on error

### Basic Usage Example

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello %s\n", "world");
    ft_printf("Number: %d, Hex: %x\n", 42, 255);
    ft_printf("Pointer: %p\n", (void *)0x12345678);
    return (0);
}
```

### Advanced Examples

```c
#include "ft_printf.h"

int main(void)
{
    int count;
    
    // Character output
    count = ft_printf("Character: %c\n", 'A');
    ft_printf("Wrote %d characters\n", count);
    
    // String and pointer output
    ft_printf("String: %s, Pointer: %p\n", "test", (void *)&count);
    
    // Various integer formats
    ft_printf("Signed: %d, Unsigned: %u\n", -42, 42);
    
    // Hexadecimal formats
    ft_printf("Lowercase: %x, Uppercase: %X\n", 255, 255);
    
    // NULL handling
    ft_printf("Null string: %s, Null pointer: %p\n", NULL, NULL);
    
    // Literal percent
    ft_printf("Discount: 50%%\n");
    
    return (0);
}
```

### Compilation of Examples

```bash
# Using the static library
cc -Wall -Wextra -Werror example.c -L. -lftprintf -o example
./example

# Using source files directly
cc -Wall -Wextra -Werror example.c ft_printf.c put_hex_ptr.c put_char_str.c put_ints.c utilities.c -o example
./example
```

---

<br>

## Project Structure

```
ft_printf/
├── Makefile                 # Build system with compilation and testing targets
├── ft_printf.h              # Header file with function declarations
├── ft_printf.c              # Core implementation with format parsing and dispatcher
├── put_hex_ptr.c            # Hexadecimal and pointer output functions
├── put_char_str.c           # Character and string output functions
├── put_ints.c               # Integer output functions
├── utilities.c              # Helper functions for number conversion and formatting
└── README.md                # This file
```

### File Descriptions

- **Makefile**: Orchestrates compilation, testing, debugging, and code quality checks
- **ft_printf.h**: Public interface declaring the main `ft_printf()` function and helper utilities
- **ft_printf.c**: Main implementation containing format string parsing and the dispatcher function
- **put_hex_ptr.c**: Specialized functions for hexadecimal and pointer address formatting
- **put_char_str.c**: Output routines for individual characters and strings
- **put_ints.c**: Output routine for numeric values (combines signed and unsigned integers)
- **utilities.c**: General-purpose helper functions for number conversions and length calculations
- **tester_for_ft_printf.c**: Comprehensive test suite (note: excluded from 42 Moulinette submission)

---

<br>

## Supported Format Specifiers

The following format specifiers are fully implemented:

- **%c** — Character output
- **%s** — String output (with special handling for NULL pointers)
- **%p** — Pointer address in hexadecimal format
- **%d** — Signed decimal integer
- **%i** — Signed decimal integer (alias for %d)
- **%u** — Unsigned decimal integer
- **%x** — Hexadecimal lowercase (0-9, a-f)
- **%X** — Hexadecimal uppercase (0-9, A-F)
- **%%** — Literal percent character

### Not Implemented

The following are NOT implemented and will cause an error:
- Flag modifiers (#, 0, +, -, space)
- Width specifiers (e.g., %5d, %-10s)
- Precision specifiers (e.g., %.2f, %.*s)
- Length modifiers (h, hh, l, ll, L)
- Floating-point specifiers (%f, %e, %g)
- Other specifiers (%o, %n, etc.)

---

<br>

## Resources

### Official Documentation

- **man printf** — Standard C library formatted output function
- **man stdarg** — Variadic function support in C
- **C11 Standard** — ISO/IEC 9899:2011, section 7.19 (Input/output)
- **42 ft_printf Subject** — Official project requirements and specifications
- **Head First C** — David Griffiths & Dawn Griffiths
  - Covers variadic functions, function pointers, and low-level I/O
- **Linux man pages** — Available at man7.org

### Related System Calls

- **write(2)** — Low-level unbuffered output (used internally)
- **malloc(3)** — Dynamic memory allocation
- **free(3)** — Memory deallocation

---

<br>

## AI Usage Disclosure

Here is a breakdown of AI usage in this project:

### What AI Was NOT Used For

- **Project Implementation**: The core code (all `.c` and `.h` files) was written without AI assistance
- **Algorithm Design**: All algorithms and logic were designed and implemented manually
- **Core Logic**: The dispatcher, parsing, and conversion routines are original implementations

### What AI Was Used For

- **Some of the test cases**: extra test cases for more rigorous testing
- **Documentation comments**: Doxygen-style documentation comments in source files
- **README creation**: This README file was generated with AI assistance for structure and clarity

---

*Last updated: April 2026*
