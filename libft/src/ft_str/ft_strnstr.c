/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:42:17 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/04 20:48:03 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	n_len;
	char	*str;

	if (!haystack || !needle)
		return (0);
	i = 0;
	n_len = ft_strlen(needle);
	str = (char *)haystack;
	if (needle == haystack || n_len == 0)
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && needle[j] && str[i + j] == needle[j])
			j++;
		if (j == n_len)
			return (str + i);
		i++;
	}
	return (NULL);
}
