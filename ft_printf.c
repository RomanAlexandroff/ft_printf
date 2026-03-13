/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:23:09 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:23:09 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Calls a function according to the format.
 *
 * @param vl  	  The va_list with the values to print.
 * @param format  The format to print the value in.
 * @return Number of characters written, or
 *			negative value on failure.
 */
static int	dispatcher(va_list *vl, const char format)
{
	int	char_printed;

	char_printed = 0;
	if (format == 'c')
		char_printed = ft_putchar(va_arg(*vl, int));
	else if (format == 's')
		char_printed = ft_putstr(va_arg(*vl, char *));
	else if (format == 'p')
		char_printed = ft_putptr((uintptr_t)va_arg(*vl, void *), format);
	else if (format == 'd' || format == 'i')
		char_printed = put_number((long)va_arg(*vl, int));
	else if (format == 'u')
		char_printed = put_number((long)va_arg(*vl, unsigned int));
	else if (format == 'x' || format == 'X')
		char_printed = ft_puthex(va_arg(*vl, unsigned int), format);
	else if (format == '%')
		char_printed = ft_putchar('%');
	else
		char_printed = ERROR;
	return (char_printed);
}

int	ft_printf(const char *string, ...)
{
	int		i;
	va_list	vl;
	int		char_printed;
	int		err_check;

	i = 0;
	char_printed = 0;
	va_start(vl, string);
	while (string[i])
	{
		if (string[i] == '%' && string[i + 1] != '\0')
		{
			err_check = dispatcher(&vl, string[i + 1]);
			i++;
		}
		else
			err_check = ft_putchar(string[i]);
		if (err_check < 0)
			return (va_end(vl), err_check);
		char_printed += err_check;
		i++;
	}
	return (va_end(vl), char_printed);
}
