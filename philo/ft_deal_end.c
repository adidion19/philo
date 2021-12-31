/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deal_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:44:31 by adidion           #+#    #+#             */
/*   Updated: 2021/12/31 10:45:17 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->a.num_philo)
	{
		pthread_mutex_destroy(&philo->p[i].ms);
		pthread_mutex_destroy(&philo->p[i].l_f);
		i++;
	}
	pthread_mutex_destroy(&philo->a.write);
	free(philo->p);
	free(philo);
	return (0);
}

t_philo	*ft_verify_num(int *k, int *j, t_philo *philo)
{
	pthread_mutex_lock(&philo->p[*k].ms);
	if (philo->p[*k].ms_since_last_eat == -1)
	{
		*j += 1;
		pthread_mutex_unlock(&philo->p[*k].ms);
		if (*j == philo->a.num_philo)
			return (ft_free(philo));
			*k += 1;
	}
	pthread_mutex_unlock(&philo->p[*k].ms);
	return (philo);
}

t_philo	*ft_verify_death(int i, t_philo *philo)
{
	pthread_mutex_lock(&philo->p[i].ms);
	if (philo->p[i].ms_since_last_eat != -1 && actual_time()
		- philo->p[i].ms_since_last_eat >= philo->p[i].pa->time_to_die)
	{
		pthread_mutex_lock(&philo->a.write);
		ft_putnbr_fd((int)actual_time() - philo->a.time, 1);
		write(1, " ", 1);
		ft_putnbr_fd((int)philo->p[i].id, 1);
		write(1, " died\n", 6);
		pthread_mutex_unlock(&philo->p[i].ms);
		philo->a.status = 1;
		pthread_mutex_unlock(&philo->a.write);
		return (ft_free(philo));
	}
	pthread_mutex_unlock(&philo->p[i].ms);
	return (philo);
}

t_philo	*ft_death(int i, t_philo *philo)
{
	int	j;
	int	k;

	k = 0;
	j = 0;
	while (1)
	{
		i = -1;
		while (philo->a.num_philo > ++i)
		{
			philo = ft_verify_num(&k, &j, philo);
			if (!philo)
				return (0);
			philo = ft_verify_death(i, philo);
			if (!philo)
				return (0);
		}
	}
	return (philo);
}
