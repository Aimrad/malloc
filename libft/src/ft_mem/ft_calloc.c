/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:22:47 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 18:39:45 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	char	*ch;

	if (((int)num_elements * (int)element_size) < 0)
		return (NULL);
	if ((int)num_elements < 0 && (int)element_size < 0)
		return (NULL);
	ch = malloc(num_elements * element_size);
	if (ch == NULL)
		return (ch);
	ft_bzero(ch, element_size * num_elements);
	return (ch);
}
