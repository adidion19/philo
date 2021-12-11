/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:39:30 by adidion           #+#    #+#             */
/*   Updated: 2021/10/25 15:55:48 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ft_simple_errors(ac, av))
		return (1);
	philo = ft_analyse_arguments(av, ac);
	if (philo.time == 0)
		return (printf("Error\nProblem in time function\n"));
	ft_create_thread(philo);
}
