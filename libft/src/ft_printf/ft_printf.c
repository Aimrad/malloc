/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 07:08:55 by marvin            #+#    #+#             */
/*   Updated: 2024/03/15 14:14:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	formatprint(va_list args, const char format)
{
	int	ftaille;

	ftaille = 0;
	if (format == 'c')
		ftaille += ft_putchar(va_arg(args, int));
	else if (format == 's')
		ftaille += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		ftaille += ft_putptr(va_arg(args, unsigned long long *));
	else if (format == 'd' || format == 'i' )
		ftaille += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		ftaille += ft_uputnbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		ftaille += convert_to_hexadecimal(va_arg(args, unsigned int), format);
	else if (format == '%')
		ftaille += ft_percent();
	return (ftaille);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		taille;

	if (!format)
		return (-1);
	i = 0;
	va_start(args, format);
	taille = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			taille += formatprint(args, format[i + 1]);
			i++;
		}
		else
			taille += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (taille);
}
// int main() {
//     // Test pour afficher une chaîne de caractères
//     ft_printf("Test d'affichage de chaîne : %s\n", "Hello, World!");

//     // Test pour afficher un caractère
//     ft_printf("Test d'affichage de caractère : %c\n", 'A');

//     // Test pour afficher un entier
//     printf("Test d'affichage d'entier : %u\n", -9223372036854775808);

//     // Test pour afficher un pointeur
//     int variable = -42;
//     ft_printf("Test d'affichage de pointeur : %p\n", (void*)&variable);

//     // Test pour afficher un nombre en hexadécimal
//     ft_printf("Test d'affichage hexadécimal : %x\n", -10);

//     // Test pour afficher un pourcentage
//     ft_printf("Test d'affichage de pourcentage : %%\n");

//     return 0;
// }
