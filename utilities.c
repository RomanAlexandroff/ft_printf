
#include "ft_printf.h"

/**
 * @brief Calculates length of a number in a given base,
 * 			including the minus sign if applicable.
 *
 * @param num  	Number to evaluate.
 * @param base  Base of the number.
 * @return Quantity of digits (and signs) in a number.
 */
int	num_len(long long num, int base)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	if (num < 0)
		len += 1;
	while (num != 0)
	{
		len++;
		num /= base;
	}
	return (len);
}

/**
 * @brief Prints a number in hexadecimal format.
 *
 * This function prints unsigned integers and pointer
 * values in hexadecimal notation. Letters are printed
 * in lowercase for format 'x' or 'p', and uppercase
 * for format 'X'.
 *
 * @param num    Value to print (integer or pointer cast).
 * @param format 'x' for lowercase, 'X' for uppercase,
 *               'p' for pointer lowercase hex.
 * @return Negative value on failure.
 */
int	put_hex(uintptr_t num, const char format)
{
	int	err_check;

	if (num >= HEX_BASE)
	{
		err_check = put_hex(num / HEX_BASE, format);
		if (err_check < 0)
			return (err_check);
		err_check = put_hex(num % HEX_BASE, format);
		if (err_check < 0)
			return (err_check);
	}
	else
	{
		if (num <= 9)
			err_check = ft_putchar((num + '0'));
		else
		{
			if (format == 'x' || format == 'p')
				err_check = ft_putchar((num - 10 + 'a'));
			if (format == 'X')
				err_check = ft_putchar((num - 10 + 'A'));
		}
	}
	return (err_check);
}

/**
 * @brief Fills a string with digits from a positive number.
 *
 * @param str  Buffer where digits are written.
 * @param num  Positive number to convert.
 * @param len  Index of the last position in the buffer.
 * @return Nothing. The buffer is modified in place.
 */
static void	num_to_char(char *str, long num, int len)
{
	while (num > 0 && len >= 0)
	{
		str[len--] = num % DEC_BASE + '0';
		num /= DEC_BASE;
	}
}

/**
 * @brief Converts a long integer to a newly allocated
 *        null-terminated string.
 *
 * Supports negative numbers and zero. Does not support
 * minimum value of type long (LONG_MIN) - undefined
 * behaviour. The caller shall free the allocated memory.
 *
 * @param num  Number to convert.
 * @return Pointer to allocated string, or NULL
 *         on allocation failure.
 */
char	*ft_ltoa(long num)
{
	char	*str;
	int		len;

	len = num_len((long long)num, DEC_BASE);
	str = malloc(sizeof(char) * (len + NUL_TERM));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	num_to_char(str, num, len);
	return (str);
}
