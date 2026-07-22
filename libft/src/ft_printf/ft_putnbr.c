/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:33:46 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 21:02:54 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putnbr(int nb)
{
	int		digit_count;
	char	*num;

	num = ft_itoa(nb);
	if (!num)
		return (0);
	digit_count = ft_putstr(num);
	free(num);
	return (digit_count);
}
