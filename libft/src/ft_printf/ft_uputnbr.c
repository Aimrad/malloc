/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:34:50 by gtoure            #+#    #+#             */
/*   Updated: 2024/04/10 05:02:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static unsigned int	count(unsigned int i)
{
	unsigned int	count;

	count = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		count++;
		i /= 10;
	}
	return (count);
}

static char	*ft_uitoa(unsigned int nbr)
{
	char			c;
	char			*a;
	unsigned int	count_real;

	count_real = count(nbr);
	a = malloc(count_real + 1);
	if (a == NULL)
		return (NULL);
	a[count_real] = '\0';
	if (nbr == 0)
		a[0] = '0';
	while (nbr != 0)
	{
		c = nbr % 10;
		a[--count_real] = (c + '0');
		nbr /= 10;
	}
	return (a);
}

int	ft_uputnbr(unsigned int nb)
{
	int		digit_count;
	char	*num;

	num = ft_uitoa(nb);
	if (!num)
		return (0);
	digit_count = ft_putstr(num);
	free(num);
	return (digit_count);
}
