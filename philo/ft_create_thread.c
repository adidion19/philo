/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:49:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/30 17:53:08 by adidion          ###   ########.fr       */
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
	if (!p)
		return (0);
	if (p->id % 2 == 0)
		pthread_mutex_lock(p->r_f);
	else
		pthread_mutex_lock(&p->l_f);
	p = ft_write_mutex(p, 1);
	if (!p)
		return (0);
	p = ft_write_mutex(p, 2);
	if (!p)
		return (0);
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
	if (!p)
		return (0);
	ft_usleep(p->pa->time_to_sleep);
	return (p);
}

t_p	*ft_routine(t_p *p)
{
	while (p->num_eat)
	{
		p = ft_eat(p);
		if (!p)
			return (0);
		if (!p->num_eat)
			break ;
		p = ft_sleep(p);
		if (!p)
			return (0);
		p = ft_write_mutex(p, 4);
		if (!p)
			return (0);
	}
	return (p);
}

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

t_philo	*ft_verify_num(int *k, int *j, t_philo *philo)
{
	pthread_mutex_lock(&philo->p[*k].ms);
	if (philo->p[*k].ms_since_last_eat == -1)
	{
		*j += 1;
		pthread_mutex_unlock(&philo->p[*k].ms);
		if (*j == philo->a.num_philo)
			return (0);
			*k += 1;
	}
	pthread_mutex_unlock(&philo->p[*k].ms);
	return (philo);
}

t_philo	*ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	//while (i < philo->a.num_philo)
	//{
		//pthread_mutex_destroy(&philo->p[i].ms);
		//pthread_mutex_destroy(&philo->p[i].l_f);
	//	i++;
	//}
	//pthread_mutex_destroy(&philo->a.write);
	//free(philo->p);
	//free(philo);
	return (0);
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
		return (0);
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
				return (ft_free(philo));
		}
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
