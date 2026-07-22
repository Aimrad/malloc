/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:25:20 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 18:38:56 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	count(long i)
{
	unsigned long	count;

	if (i <= 0)
		count = 1;
	else
		count = 0;
	while (i != 0)
	{
		count++;
		i /= 10;
	}
	return (count);
}

char	*ft_itoa(long nbr)
{
	char			c;
	char			*a;
	unsigned long	count_real;

	count_real = count(nbr);
	a = malloc(count_real + 1);
	if (a == NULL)
		return (NULL);
	a[count_real] = '\0';
	if (nbr == 0)
		a[0] = '0';
	if (nbr < 0)
	{
		a[0] = '-';
	}
	while (nbr != 0)
	{
		c = nbr % 10;
		if (nbr < 0)
			c = -c;
		a[--count_real] = (c + '0');
		nbr /= 10;
	}
	return (a);
}
