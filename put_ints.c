/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ints.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:23:30 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:23:30 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief Shared routine to prepare 'int' and
 *		'unsigned int' values for printing.
 *
 * @param num  numeric value to print.
 * @return Number of characters written, or
 *			negative value on failure.
 */
int	put_number(long num)
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
