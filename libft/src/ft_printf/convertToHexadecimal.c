/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertToHexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:17:53 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 20:56:18 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	convert(unsigned int num, const char format)
{
	if (num >= 16)
	{
		convert(num / 16, format);
		convert(num % 16, format);
	}
	else
	{
		if (num < 10)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	convert_to_hexadecimal(unsigned int number, char format)
{
	int		i;

	i = 0;
	if (number == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
		convert(number, format);
	while (number != 0)
	{
		number /= 16;
		i++;
	}
	return (i);
}
