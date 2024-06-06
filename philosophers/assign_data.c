/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:23:35 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 16:22:07 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forks_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_number)
	{
		if (pthread_mutex_init(&data->forks[i].lock, NULL))
			return (1);
		data->forks[i].in_use = 0;
		i++;
	}
	return (0);
}

static void	philo_init(t_data *data, char **args, int argc, int i)
{
	while (i < data->p_number)
	{
		data->philo[i].index = i;
		data->philo[i].p_num = ft_atoi(args[1]);
		data->philo[i].t_die = ft_atoi(args[2]);
		data->philo[i].t_eat = ft_atoi(args[3]);
		data->philo[i].t_sleep = (long long) ft_atoi(args[4]);
		if (argc == 6)
			data->philo[i].eat_count = ft_atoi(args[5]);
		else if (argc == 5)
			data->philo[i].eat_count = -1;
		data->philo[i].death = &data->death;
		data->philo[i].t_start = &data->t_s;
		data->philo[i].t_now = data->t_s;
		data->philo[i].t_last_eat = data->t_s;
		data->philo[i].all_done_eating = &data->all_done_eating;
		data->philo[i].d_lock = &data->death_lock;
		data->philo[i].e_c_lock = &data->eat_count_lock;
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].stop_all = &data->stop_all;
		i++;
	}
}

static void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_number)
	{
		if (i < data->p_number - 1)
		{
			data->philo[i].fork_l = &data->forks[i];
			data->philo[i].fork_r = &data->forks[i + 1];
		}
		else if (i == data->p_number - 1)
		{
			data->philo[i].fork_l = &data->forks[i];
			data->philo[i].fork_r = &data->forks[0];
		}
		i++;
	}
}

static int	data_mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->death_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->eat_count_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	return (0);
}

int	assign_data(t_data *data, char **args, int argc)
{
	gettimeofday(&data->t_s, NULL);
	data->start_ts = data->t_s.tv_sec * 1000LL + data->t_s.tv_usec / 1000;
	data->p_number = ft_atoi(args[1]);
	data->death = 0;
	data->stop_all = 0;
	if (argc == 6)
		data->all_done_eating = data->p_number;
	else if (argc == 5)
		data->all_done_eating = -1;
	if (data_mutex_init(data))
		return (1);
	if (forks_init(data))
		return (1);
	philo_init(data, args, argc, 0);
	assign_forks(data);
	return (0);
}
