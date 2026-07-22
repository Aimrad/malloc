/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarfi <lgarfi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:33:04 by gtoure            #+#    #+#             */
/*   Updated: 2024/11/20 16:02:35 by lgarfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	countword(const char *s, char c)
{
	size_t	i;
	size_t	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (word);
}

static char	*get_word(const char *s, char c, size_t *i)
{
	size_t	j;
	size_t	k;
	char	*sub;

	j = *i;
	k = 0;
	while (s[j] != c && s[j])
		j++;
	sub = (char *)malloc((j - *i + 1) * 1);
	if (!sub)
		return (NULL);
	while (*i < j)
		sub[k++] = s[(*i)++];
	sub[k] = '\0';
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	iresult;
	char	**result;

	result = NULL;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (countword(s, c) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	iresult = 0;
	while (s[i])
	{
		if (s[i] != c)
			result[iresult++] = get_word(s, c, &i);
		else
			i++;
	}
	result[countword(s, c)] = NULL;
	return (result);
}
