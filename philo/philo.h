/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adidion <adidion@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:09:37 by adidion           #+#    #+#             */
/*   Updated: 2021/10/25 15:55:39 by adidion          ###   ########.fr       */
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

typedef struct s_p
{
	pthread_mutex_t	mutex;
	int				i;
}	t_p;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				place;
	pthread_mutex_t	l_f;
	pthread_mutex_t	*r_f;
}	t_philosopher;

typedef struct s_philo
{
	long			num_philo;
	long			num_fork;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_eat;
	long			time;
	int				place;
	t_philosopher	*philosopher;
}	t_philo;

int			ft_simple_errors(int ac, char **av);
long		ft_strtol(const char *str);
int			ft_isnum(char *str);
t_philo		ft_analyse_arguments(char **av, int ac);
void		ft_create_thread(t_philo philo);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
int			ft_strlen(char *str);

#endif
