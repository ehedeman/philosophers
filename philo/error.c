/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:05:22 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:16:37 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	if (data)
	{
		if (data->t_list)
			free(data->t_list);
		free(data);
	}
}

int	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_num)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_destroy(&data->death_lock) != 0)
		return (-1);
	if (pthread_mutex_destroy(&data->write_lock) != 0)
		return (-1);
	return (0);
}

int	philo_error(t_philo *philo, int error_code)
{
	if (error_code == MUTEX_LOCK)
		printf("Error: Thread %i failed to lock mutex.", philo->id);
	if (error_code == MUTEX_UNLOCK)
		printf("Error: Thread %i failed to unlock mutex.", philo->id);
	philo->state = ERR;
	return (-1);
}

int	data_error(t_data *data, int error_code)
{
	if (error_code == MUTEX_INIT)
		printf("Error: failed to initialize mutex.");
	if (error_code == ALLOCATION_ERR)
		printf("Error: allocation failed.");
	if (error_code == THREAD_ERR)
	{
		printf("Error: failed to initialize threads.");
		destroy_all(data);
	}
	if (error_code == MUTEX_DESTROY)
		printf("Error: failed to destroy mutex.");
	free_all(data);
	return (0);
}
