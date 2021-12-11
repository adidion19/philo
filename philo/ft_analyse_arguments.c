/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:02:25 by adidion           #+#    #+#             */
/*   Updated: 2021/10/25 15:55:29 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	ft_analyse_arguments(char **av, int ac)
{
	t_philo	philo;

	philo.num_philo = ft_strtol(av[1]);
	philo.num_fork = ft_strtol(av[1]);
	philo.time_to_die = ft_strtol(av[2]);
	philo.time_to_eat = ft_strtol(av[3]);
	philo.time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
		philo.num_of_eat = ft_strtol(av[5]);
	else
		philo.num_of_eat = 0;
	philo.time = actual_time();
	return (philo);
}
