/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:12:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:19:14 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <math.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef enum e_action
{
	ERR = -1,
	THINK = 0,
	EAT = 1,
	SLEEP = 2,
	T_FORK = 3,
	DIE = 4,
}			t_action;

typedef enum e_errors
{
	MUTEX_INIT = 1,
	ALLOCATION_ERR = 2,
	THREAD_ERR = 3,
	MUTEX_LOCK = 4,
	MUTEX_UNLOCK = 5,
	MUTEX_DESTROY = 6,
}			t_errors;

typedef struct s_philo
{
	int				id;
	int				p_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	struct timeval	t_now;
	struct timeval	t_start;
	struct timeval	t_last_eat;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*write_lock;
	int				*done_eating;
	int				is_eating;
	int				eat_count;
	int				*stop_all;
	int				state;
}				t_philo;

typedef struct s_data
{
	t_philo			philo[300];
	pthread_mutex_t	forks[300];
	pthread_t		*t_list;
	pthread_t		*monitor_thread;
	int				p_num;
	int				done_eating;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	write_lock;
	struct timeval	t_s;
	int				stop_all;
}				t_data;

int			assign_data(t_data *data, char **args, int argc);

int			ft_atoi(const char *str);

void		free_all(t_data *data);
int			destroy_all(t_data *data);
int			philo_error(t_philo *philo, int error_code);
int			data_error(t_data *data, int error_code);

int			check_input(int argc, char **argv);

void		write_monitor(t_philo *philo, char *msg);
int			check_if_dead(t_philo *philo);

void		*monitor(void *data);

int			states(t_philo *philo);

int			t_wait(t_philo *philo, long long time);

void		*philo(void	*args);

long long	timediff(struct timeval *t1, struct timeval *t2);
long long	get_timestamp(t_philo *philo);
int			write_lock(t_philo *philo, char *msg);
int			t_wait(t_philo *philo, long long time);

int			threads_init(t_data *data);

#endif