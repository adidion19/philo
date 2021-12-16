/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:39:30 by adidion           #+#    #+#             */
/*   Updated: 2021/12/13 17:39:11 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (ft_simple_errors(ac, av))
		return (1);
	philo->p = malloc(sizeof(t_p) * ((ft_strtol(av[1]) + 1)));
	if (!philo->p)
		exit(EXIT_FAILURE);
	philo = ft_analyse_arguments(av, ac, philo);
	ft_create_thread(philo);
	free(philo->p);
}
