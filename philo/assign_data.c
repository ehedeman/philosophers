/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:23:35 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:16:13 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_data *data, char **args, int argc, int i)
{
	while (i < data->p_num)
	{
		data->philo[i].id = i + 1;
		data->philo[i].p_num = ft_atoi(args[1]);
		data->philo[i].t_die = ft_atoi(args[2]);
		data->philo[i].t_eat = ft_atoi(args[3]);
		data->philo[i].t_sleep = ft_atoi(args[4]);
		if (argc == 6)
			data->philo[i].eat_count = ft_atoi(args[5]);
		else if (argc == 5)
			data->philo[i].eat_count = -1;
		data->philo[i].t_start = data->t_s;
		data->philo[i].t_now = data->t_s;
		data->philo[i].t_last_eat = data->t_s;
		data->philo[i].death_lock = &data->death_lock;
		data->philo[i].write_lock = &data->write_lock;
		data->philo[i].stop_all = &data->stop_all;
		data->philo[i].done_eating = &data->done_eating;
		data->philo[i].is_eating = 0;
		data->philo[i].state = THINK;
		i++;
	}
}

static void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_num)
	{
		if (i < data->p_num - 1)
		{
			data->philo[i].fork_l = &data->forks[i];
			data->philo[i].fork_r = &data->forks[i + 1];
		}
		else if (i == data->p_num - 1)
		{
			data->philo[i].fork_l = &data->forks[i];
			data->philo[i].fork_r = &data->forks[0];
		}
		i++;
	}
}

static int	data_mutex_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (1);
	return (0);
}

int	assign_data(t_data *data, char **args, int argc)
{
	gettimeofday(&data->t_s, NULL);
	data->p_num = ft_atoi(args[1]);
	data->stop_all = 0;
	if (argc == 6)
		data->done_eating = data->p_num;
	else if (argc == 5)
		data->done_eating = -1;
	if (data_mutex_init(data))
		return (1);
	philo_init(data, args, argc, 0);
	assign_forks(data);
	return (0);
}
