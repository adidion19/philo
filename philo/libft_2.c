/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:18:42 by adidion           #+#    #+#             */
/*   Updated: 2021/12/30 16:37:15 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	a;
	char			c;

	a = nb;
	if (a >= 10)
	{
		c = a % 10 + '0';
		ft_putnbr_fd(a / 10, fd);
		write(fd, &c, 1);
	}
	else
	{
		c = a + '0';
		write(fd, &c, 1);
	}
}
