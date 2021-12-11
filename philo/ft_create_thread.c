/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:49:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/11 15:21:26 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threas(void *place)
{
	t_philo	*philo;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&mutex);
	philo = (t_philo *)place;
	printf("philo %d arrive a table\n", philo->philosopher[philo->place].place);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	ft_create_thread(t_philo philo)
{

	philo.philosopher = malloc(sizeof(t_philosopher) * (philo.num_philo) + 1);
	if (!philo.philosopher)
		exit(EXIT_FAILURE);
	philo.place = -1;
	while (philo.num_philo >= ++philo.place)
	{
		philo.philosopher[philo.place].place = philo.place;
		pthread_create(&philo.philosopher[philo.place].thread, NULL, threas, &philo);
	}
	free(philo.philosopher);
}
