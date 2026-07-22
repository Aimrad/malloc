/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:31:10 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 21:03:19 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_putptrbis(unsigned long long num)
{
	if (num >= 16)
	{
		ft_putptrbis(num / 16);
		ft_putptrbis(num % 16);
	}
	else
	{
		if (num < 10)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_putptr(unsigned long long *number)
{
	int					i;
	unsigned long long	num;

	if (!number)
		return (write(1, "(nil)", 5));
	i = 0;
	i += write(1, "0x", 2);
	if (number == 0)
		i += write(1, "0", 1);
	else
		ft_putptrbis((unsigned long long)number);
	num = (unsigned long long)number;
	while (num != 0)
	{
		num /= 16;
		i++;
	}
	return (i);
}
