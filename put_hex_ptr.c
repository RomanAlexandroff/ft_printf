
#include "ft_printf.h"

/**
 * @brief Prints a pointer address in hexadecimal format.
 * 			If the pointer is NULL, the function prints
 * 			"(nil)", which is the Linux printf style.
 *
 * @param ptr     Pointer value to print.
 * @param format  Hexadecimal format specifier.
 * @return Number of characters written, or
 *			negative value on failure.
 */
int	ft_putptr(uintptr_t ptr, const char format)
{
	int	char_printed;
	int	err_check;

	if (!ptr)
		return (write(FD, "(nil)", 5));		// Linux
//		return (write(FD, "0x0", 3));		// macOS	
	err_check = write(FD, "0x", 2);
	if (err_check < 0)
		return (err_check);
	char_printed = err_check;
	put_hex(ptr, format);
	char_printed += num_len((long long)ptr, HEX_BASE);
	return (char_printed);
}

/**
 * @brief Prints an unsigned integer in hexadecimal format.
 *
 * @param num     Number to print.
 * @param format  Hexadecimal format specifier ('x' or 'X').
 * @return Number of characters written, or
 *			negative value on failure.
 */
int	ft_puthex(unsigned int num, const char format)
{
	int	err_check;

	if (num == 0)
		return (write(FD, "0", 1));
	else
	{
		err_check = put_hex((uintptr_t)num, format);
		if (err_check < 0)
			return (err_check);
	}
	return (num_len((long long)num, HEX_BASE));
}
