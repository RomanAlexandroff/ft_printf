
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
//# include <stdint.h>

# define DEC_BASE	10
# define HEX_BASE	16
# define ERROR		-1
# define NUL_TERM	1
# define FD			1

int			ft_putchar(int c);
int			ft_putstr(char *str);
int			put_number(long num);
int			ft_puthex(unsigned int num, const char format);
int			ft_putptr(uintptr_t ptr, const char format);
int			ft_printf(const char *format, ...);
int			put_hex(uintptr_t num, const char format);
int			num_len(long long num, int base);
char		*ft_ltoa(long num);

#endif

/*			TO-DO LIST
	- check if it compiles 
	- check if it compiles without the <stdint.h> library for uinptr_t type
		and if it does compile, remove the <stdint.h> library
	- check if real printf says 0x0 or (nil) when trying to print NULL pointer
		because macOS printf prints 0x0, but Debian printf prints (nil), and
		then change it accordingly in ft_printf_hex_ptr.c / ft_putptr()
	- check that the program prints INT_MIN as -2147483648
	- check that Makefile works (all the rules exept "git")
	- check that Makefile compiles the library with correct name
	- make sure the subject does not have any changes, that I have not implemented
	- add heads to all the files
	- move the tester_for_ft_printf.c file into some other folder before submition,
		because this file does not comply with the Norm and will cause Moulinette to fail you !
	- run Norminette (make norm) with all the flags and fix whatever it says
*/