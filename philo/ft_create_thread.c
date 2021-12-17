/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:49:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/17 15:40:49 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	a;
	char c;

	a = nb;
	if (a >= 10)
	{
		c = a % 10 + '0';
		ft_putnbr_fd(a / 10, fd);
		write(fd, &c, 1);
	}
	else
	{
		c = a + '0';
		write(fd, &c, 1);
	}
}

t_p	*ft_write_mutex(t_p *p, int bool)
{
	pthread_mutex_lock(&p->pa->write);
	ft_putnbr_fd((int)actual_time() - p->pa->time, 1);
	write(1, " ", 1);
	ft_putnbr_fd((int)p->id, 1);
	//if (actual_time() - p->ms_since_last_eat <= p->pa->time_to_die)
	//{
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
	//}
	//else
	//{
	//	write(1, " died\n", 6);
	//	p->pa->status = p->id;
	//	return (0);
	//}
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
	//if (actual_time() - p->ms_since_last_eat <= p->pa->time_to_die)
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

void	*threas(void *phi)
{
	t_p		*p;

	p = (t_p *)phi;
	if (p->pa->num_philo % 2 == 1)
	{
		if (p->id % 3 == 2)
			ft_usleep(p->pa->time_to_eat + p->pa->time_to_eat / 10);
		if (p->id % 3 == 1)
			ft_usleep(p->pa->time_to_eat / 10);
	}
	else if (p->id % 2 == 0)
		ft_usleep(p->pa->time_to_eat / 10);
	//p->ms_since_last_eat = actual_time();
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
	int				i;

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

void	ft_create_thread(t_philo *philo)
{
	int	i;
	int	philo_num;

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
	while (0 < --i)
		pthread_join(philo->p[i].thread, NULL);
	//while (!philo->a.status)
	//	;
	int j = 0;
	philo_num = 0;
	while (1)
	{
		i = -1;
		while (philo->a.num_philo > ++i)
		{
			pthread_mutex_lock(&philo->p[j].ms);
			if (philo->p[j].ms_since_last_eat == -1)
			{
				j++;
				pthread_mutex_unlock(&philo->p[j].ms);
				if (j == philo->a.num_philo)
					return ; // ca rentre jamais ici
			}
			pthread_mutex_unlock(&philo->p[j].ms);
			pthread_mutex_lock(&philo->p[i].ms);
			if (philo->p[i].ms_since_last_eat != -1 && actual_time() - philo->p[i].ms_since_last_eat > philo->p[i].pa->time_to_die)
			{
				pthread_mutex_unlock(&philo->a.write);
				ft_putnbr_fd((int)actual_time() - philo->a.time, 1);
				write(1, " ", 1);
				ft_putnbr_fd((int)philo->p[i].id, 1);
				write(1, " died\n", 6);
				pthread_mutex_unlock(&philo->p[i].ms);
				return ;
				//p->pa->status = p->id;
			}
			pthread_mutex_unlock(&philo->p[i].ms);
		}
	}
}
