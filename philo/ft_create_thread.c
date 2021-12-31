/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:49:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/31 10:47:20 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threas(void *phi)
{
	t_p		*p;

	p = (t_p *)phi;
	if (p->pa->num_philo % 2 == 1 && p->id % 3 == 2)
		ft_usleep(p->pa->time_to_eat + p->pa->time_to_eat / 10);
	if (p->pa->num_philo % 2 == 1 && p->id % 3 == 1)
		ft_usleep(p->pa->time_to_eat / 10);
	if (p->pa->num_philo % 2 == 0 && p->id % 2 == 0)
		ft_usleep(p->pa->time_to_eat / 10);
	p = ft_routine(p);
	if (!p->num_eat)
	{
		pthread_mutex_lock(&p->ms);
		p->ms_since_last_eat = -1;
		pthread_mutex_unlock(&p->ms);
		return (phi);
	}
	return (0);
}

t_philo	*ft_mutex_init(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->a.num_philo)
	{
		philo->p[i].id = i + 1;
		pthread_mutex_init(&philo ->p[i].l_f, NULL);
		pthread_mutex_init(&philo ->p[i].ms, NULL);
		if (i == philo->a.num_philo - 1)
			philo->p[i].r_f = &philo->p[0].l_f;
		else
			philo->p[i].r_f = &philo->p[i + 1].l_f;
		i++;
	}
	return (philo);
}

t_philo	*ft_join(int i, t_philo *philo)
{
	i++;
	while (0 < --i)
		pthread_join(philo->p[i].thread, NULL);
	philo = ft_death(i, philo);
	return (philo);
}

void	ft_create_thread(t_philo *philo)
{
	int	i;

	i = -1;
	philo = ft_mutex_init(philo);
	pthread_mutex_init(&philo->a.write, NULL);
	philo->a.time = actual_time();
	philo->a.status = 0;
	while (philo->a.num_philo > ++i)
	{
		philo->p[i].num_eat = philo->a.num_of_eat;
		philo->p[i].place = i;
		philo->p[i].pa = &philo->a;
		philo->p[i].ms_since_last_eat = actual_time();
		pthread_create(&philo->p->thread, NULL, threas, &philo->p[i]);
	}
	philo = ft_join(i, philo);
}
