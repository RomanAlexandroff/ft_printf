
#include "ft_printf.h"

/**
 * @brief Shared routine to prepare 'int' and
 *		'unsigned int' values for printing.
 *
 * @param num  numeric value to print.
 * @return Number of characters written, or
 *			negative value on failure.
 */
static int	put_any_number(long num)
{
	char	*num_str;
	int		char_printed;

	if (num == 0)
		return (write(FD, "0", 1));
	num_str = ft_ltoa(num);
	if (!num_str)
		return (ERROR);
	char_printed = ft_putstr(num_str);
	return (free(num_str), char_printed);
}

/**
 * @brief Casts 'unsigned int' from va_list to
 *		'long' for the shared printing routine.
 *
 * @param num  Unsigned integer to print.
 * @return Number of characters written.
 *			negative value on failure.
 */
int	ft_putunsigned(unsigned int num)
{
	return (put_any_number((long)num));
}

/**
 * @brief Casts int value from va_list to 'long'
 *		for the shared printing routine.
 *
 * @param num  Signed integer to print.
 * @return Number of characters written.
 *			negative value on failure.
 */
int	ft_putint(int num)
{
	return (put_any_number((long)num));
}
