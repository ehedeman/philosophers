/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:12:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 16:23:22 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_action
{
	THINK = 0,
	EAT = 1,
	SLEEP = 2,
	T_FORK = 3,
	DIE = 4,
}			t_action;

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	lock;
}				t_fork;

typedef struct s_philo
{
	int				index;
	int				p_num;
	int				t_die;
	int				t_eat;
	long long		t_sleep;
	t_fork			*fork_l;
	t_fork			*fork_r;
	struct timeval	t_now;
	struct timeval	*t_start;
	struct timeval	t_last_eat;
	pthread_mutex_t	*d_lock;
	pthread_mutex_t	*e_c_lock;
	pthread_mutex_t	*write_lock;
	int				*all_done_eating;
	int				eat_count;
	int				*death;
	int				has_eaten;
	int				*stop_all;
	int				action;
}				t_philo;

typedef struct s_data
{
	t_philo			philo[300];
	t_fork			forks[300];
	pthread_t		*t_list;
	int				p_number;
	int				death;
	int				all_done_eating;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eat_count_lock;
	pthread_mutex_t	write_lock;
	struct timeval	t_s;
	long long		start_ts;
	int				stop_all;
}				t_data;

int			assign_data(t_data *data, char **args, int argc);
int			check_input(int argc, char **argv);
void		free_all(t_data *data, int error);
int			ft_atoi(const char *str);

int			check_for_death(t_philo *philo);
int			check_if_dead(t_philo *philo);
int			check_a_d_e(t_philo *philo);
int			check_eat_count(t_philo *philo);

void		write_lock(t_philo *philo, char *msg);
int			actions(t_philo *philo);
int			try_take_forks(t_philo *philo);
int		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

long long	timediff(struct timeval *t1, struct timeval *t2);
long long	get_timestamp(t_philo *philo);

int			t_wait(t_philo *philo, long long time);
void		*philo(void	*args);
void		*threads_init(t_data *data);

#endif