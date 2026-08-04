/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 05:05:22 by marvin            #+#    #+#             */
/*   Updated: 2024/04/10 05:07:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		formatprint(va_list args, const char format);
int		ft_putnbr(int nb);
int		ft_putptr(unsigned long long *number);
int		ft_uputnbr(unsigned int nbr);
int		convert_to_hexadecimal(unsigned int number, char format);
int		ft_percent(void);
int		ft_putstr(char *s);

#endif