/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:08:57 by adidion           #+#    #+#             */
/*   Updated: 2021/10/19 17:09:00 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_simple_errors(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (printf("Error :\nYou should give 4 or 5 argument\n"));
	i = 0;
	while (av[++i])
		if (ft_isnum(av[i]) == 0)
			return (printf("Error\nThe arguments must be entire postive numbers\n"));
	i = 0;
	while (av[++i])
		if (ft_strtol(av[i]) <= 0)
		{
			return (printf("Error\nThe numbers could not be too big or = 0\n"));
		}
	return (0);
}
