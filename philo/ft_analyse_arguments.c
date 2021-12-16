/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:02:25 by adidion           #+#    #+#             */
/*   Updated: 2021/12/13 17:00:28 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_analyse_arguments(char **av, int ac, t_philo *philo)
{
	philo->a.num_philo = ft_strtol(av[1]);
	philo->a.num_fork = ft_strtol(av[1]);
	philo->a.time_to_die = ft_strtol(av[2]);
	philo->a.time_to_eat = ft_strtol(av[3]);
	philo->a.time_to_sleep = ft_strtol(av[4]);
	if (ac == 6)
		philo->a.num_of_eat = ft_strtol(av[5]);
	else
		philo->a.num_of_eat = -1;
	return (philo);
}
