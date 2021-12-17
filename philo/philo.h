/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:09:37 by adidion           #+#    #+#             */
/*   Updated: 2021/12/17 15:27:05 by adidion          ###   ########.fr       */
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

typedef struct s_ph
{
	pthread_mutex_t	mutex;
	int				i;
}	t_ph;

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

#endif
