/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:46:20 by adidion           #+#    #+#             */
/*   Updated: 2021/12/31 10:47:25 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_p	*ft_write_mutex(t_p *p, int bool)
{
	pthread_mutex_lock(&p->pa->write);
	if (p->pa->status)
		pthread_mutex_unlock(&p->pa->write);
	if (p->pa->status)
		return (p);
	ft_putnbr_fd((int)actual_time() - p->pa->time, 1);
	write(1, " ", 1);
	ft_putnbr_fd((int)p->id, 1);
	if (bool == 1)
		write(1, " has taken a fork\n", 18);
	if (bool == 2)
		write(1, " is eating\n", 11);
	if (bool == 3)
		write(1, " is sleeping\n", 14);
	if (bool == 4)
		write(1, " is thinking\n", 14);
	pthread_mutex_unlock(&p->pa->write);
	return (p);
}

t_p	*ft_eat(t_p *p)
{
	if (p->id % 2 == 0)
		pthread_mutex_lock(&p->l_f);
	else
		pthread_mutex_lock(p->r_f);
	p = ft_write_mutex(p, 1);
	if (p->id % 2 == 0)
		pthread_mutex_lock(p->r_f);
	else
		pthread_mutex_lock(&p->l_f);
	p = ft_write_mutex(p, 1);
	p = ft_write_mutex(p, 2);
	p->num_eat--;
	pthread_mutex_lock(&p->ms);
	p->ms_since_last_eat = actual_time();
	pthread_mutex_unlock(&p->ms);
	ft_usleep(p->pa->time_to_eat);
	pthread_mutex_unlock(p->r_f);
	pthread_mutex_unlock(&p->l_f);
	return (p);
}

t_p	*ft_sleep(t_p *p)
{
	p = ft_write_mutex(p, 3);
	ft_usleep(p->pa->time_to_sleep);
	return (p);
}

t_p	*ft_routine(t_p *p)
{
	while (p->num_eat)
	{
		p = ft_eat(p);
		if (!p->num_eat)
			break ;
		p = ft_sleep(p);
		p = ft_write_mutex(p, 4);
	}
	return (p);
}
