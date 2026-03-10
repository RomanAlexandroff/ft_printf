#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdint.h>

# define DEC_BASE	10
# define HEX_BASE	16
# define ERROR		-1
# define NUL_TERM	1
# define FD			1

int			ft_putchar(int c);
int			ft_putstr(char *str);
int			ft_putint(int num);
int			ft_putunsigned(unsigned int num);
int			ft_puthex(unsigned int num, const char format);
int			ft_putptr(uintptr_t ptr, const char format);
int			ft_printf(const char *format, ...);
int			put_hex(uintptr_t num, const char format);
int			num_len(long long num, int base);
char		*ft_ltoa(long num);

#endif


/*			TO-DO LIST

	- add heads to all the files
	- check how ft_printf should handle malloc fails
	- run Norminette with all the flags and fix whatever it says
		(ignore the main_tests.c file)
	- check if it compiles
	- check if it compiles without the <stdint.h> library for uinptr_t type
		and if it does compile, remove the <stdint.h> library
	- check if real printf says 0x0 or (nil) when trying to print NULL pointer
		because macOS printf prints 0x0, but Debian printf prints (nil)
	- check that the program prints INT_MIN as -2147483648
	- remove the main-tests.c file
	- remove any files that are not part of the task
	- check that Makefile works
	- check that Makefile compiles the library with correct name
*/