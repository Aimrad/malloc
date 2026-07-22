/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:50:54 by gtoure            #+#    #+#             */
/*   Updated: 2024/05/14 15:51:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_expand_gnl
{
	size_t	size;
	char	*result;
	char	*expanded;
	int		i;
	int		j;
	int		k;
}	t_expand_gnl;

char	*get_next_line(int fd, int flag);
char	*ft_gnlstrchr(char *s, int c);
char	*ft_gnlstrjoin(char *s1, char *s2);
size_t	ft_gnlstrlen(char *str);
char	*ft_gnlstrdup(char *s);

#endif
