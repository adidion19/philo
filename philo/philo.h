/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:09:37 by adidion           #+#    #+#             */
/*   Updated: 2021/12/31 10:48:59 by adidion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_a
{
	long			num_philo;
	long			num_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_eat;
	pthread_mutex_t	write;
	long			time;
	int				status;
}	t_a;

typedef struct s_p
{
	pthread_t		thread;
	int				place;
	pthread_mutex_t	l_f;
	pthread_mutex_t	*r_f;
	pthread_mutex_t	ms;
	int				id;
	int				num_eat;
	long int		ms_since_last_eat;
	t_a				*pa;
}	t_p;

typedef struct s_philo
{
	t_a				a;
	t_p				*p;
}	t_philo;

int			ft_simple_errors(int ac, char **av);
long		ft_strtol(const char *str);
int			ft_isnum(char *str);
t_philo		*ft_analyse_arguments(char **av, int ac, t_philo *philo);
void		ft_create_thread(t_philo *philo);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
int			ft_strlen(char *str);
void		ft_putchar(char c, int fd);
void		ft_putnbr_fd(int nb, int fd);
t_p			*ft_routine(t_p *p);
t_p			*ft_sleep(t_p *p);
t_p			*ft_eat(t_p *p);
t_p			*ft_write_mutex(t_p *p, int bool);
t_philo		*ft_death(int i, t_philo *philo);
t_philo		*ft_verify_death(int i, t_philo *philo);
t_philo		*ft_verify_num(int *k, int *j, t_philo *philo);
t_philo		*ft_free(t_philo *philo);

#endif
