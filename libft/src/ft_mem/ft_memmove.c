/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:30:43 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 18:39:55 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dstm;
	unsigned char	*srcm;

	if (!dst && !src)
		return (NULL);
	dstm = (unsigned char *) dst;
	srcm = (unsigned char *) src;
	if (srcm <= dstm)
	{
		srcm = srcm + len - 1;
		dstm = dstm + len - 1;
		while (len > 0)
		{
			*dstm-- = *srcm--;
			len--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
