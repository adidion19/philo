/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thread.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:49:07 by adidion           #+#    #+#             */
/*   Updated: 2021/12/15 19:00:54 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	a;

	if (nb < 0)
	{
		write(fd, "-", 1);
		a = -nb;
	}
	else
		a = nb;
	if (a >= 10)
	{
		ft_putnbr_fd(a / 10, fd);
		ft_putchar(a % 10 + '0', fd);
	}
	else
		ft_putchar(a + '0', fd);
}

int	ft_write_mutex(t_p *p, int bool)
{
	pthread_mutex_lock(&p->pa->write);
	ft_putnbr_fd((int)actual_time() - p->pa->time, 1);
	write(1, " ", 1);
	ft_putnbr_fd((int)p->id, 1);
	if (actual_time() - p->ms_since_last_eat < p->pa->time_to_die)
	{
		if (bool == 1)
			write(1, " has taken a fork\n", 18);
		if (bool == 2)
			write(1, " is eating\n", 11);
		if (bool == 3)
			write(1, " is sleeping\n", 14);
		if (bool == 4)
			write(1, " is thinking\n", 14);
		pthread_mutex_unlock(&p->pa->write);
		return (0);
	}
	else
	{
		write(1, " has died\n", 10);
		return (1);
	}
}

t_p	*ft_eat(t_p *p)
{
	if (p->id % 2 == 0)
		pthread_mutex_lock(&p->l_f);
	else
		pthread_mutex_lock(p->r_f);
	ft_write_mutex(p, 1);
	if (p->id % 2 == 0)
		pthread_mutex_lock(p->r_f);
	else
		pthread_mutex_lock(&p->l_f);
	ft_write_mutex(p, 1);
	ft_write_mutex(p, 2);
	p->num_eat--;
	p->ms_since_last_eat = actual_time();
	ft_usleep(p->pa->time_to_eat);
	pthread_mutex_unlock(p->r_f);
	pthread_mutex_unlock(&p->l_f);
	return (p);
}

void	ft_sleep(t_p *p)
{
	ft_write_mutex(p, 3);
	ft_usleep(p->pa->time_to_sleep);
}

void	*threas(void *phi)
{
	t_p		*p;

	p = (t_p *)phi;
	if (p->id % 2 == 0)
		ft_usleep(p->pa->time_to_eat / 10);
	while (p->num_eat)
	{
		p = ft_eat(p);
		if (!p->num_eat)
			break ;
		ft_sleep(p);
		ft_write_mutex(p, 4);
	}
	if (!p->num_eat)
		return (phi);
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

	i = -1;
	philo = ft_mutex_init(philo);
	pthread_mutex_init(&philo->a.write, NULL);
	philo->a.time = actual_time();
	while (philo->a.num_philo > ++i)
	{
		philo->p[i].num_eat = philo->a.num_of_eat;
		philo->p[i].place = i;
		philo->p[i].pa = &philo->a;
		philo->p[i].ms_since_last_eat = actual_time();
		pthread_create(&philo->p->thread, NULL, threas, &philo->p[i]);
	}
	while (1);
	//while (0 < --i)
	//	pthread_join(philo->p[i].thread, NULL);
}
