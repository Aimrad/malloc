/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:29:00 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 18:37:11 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*sc;

	i = 0;
	sc = (unsigned char *)s;
	while (n > 0)
	{
		if (sc[i] == (unsigned char) c)
			return (sc + i);
		i++;
		n--;
	}
	return (NULL);
}
