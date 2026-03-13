/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:23:26 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:23:26 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Writes a character to standard output.
 *
 * @param c  The character to write.
 * @return Number of characters written, or
 *			negative value on failure.
 */
int	ft_putchar(int c)
{
	return (write(FD, &c, 1));
}

/**
 * @brief Writes null-terminated string to standard output.
 *
 * @param str     Null-terminated string to write.
 * @return Number of characters written, or
 *			negative value on failure.
 */
int	ft_putstr(char *str)
{
	int	i;
	int	err_check;

	i = 0;
	if (str == NULL)
		return (write(FD, "(null)", 6));
	while (str[i])
	{
		err_check = write(FD, &str[i], 1);
		if (err_check < 0)
			return (err_check);
		i++;
	}
	return (i);
}
