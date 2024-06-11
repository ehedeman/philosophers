/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:52:42 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:17:23 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_eaten(t_philo *philo)
{
	int	i;
	int	min_eat;

	i = 0;
	if (*philo->done_eating > 0)
	{
		min_eat = *philo->done_eating;
		while (i < philo->p_num)
		{
			if (philo[i].eat_count == 0)
				min_eat--;
			i++;
		}
		if (!min_eat)
		{
			if (pthread_mutex_lock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_LOCK));
			*philo->stop_all = 1;
			if (pthread_mutex_unlock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_UNLOCK));
			write_monitor(&philo[i], NULL);
			return (1);
		}
	}
	return (0);
}

static int	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (check_if_dead(&philo[i]))
		{
			if (pthread_mutex_lock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_LOCK));
			*philo->stop_all = 1;
			if (pthread_mutex_unlock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_UNLOCK));
			write_monitor(&philo[i], "died");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_error(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->p_num)
	{
		if (philo[i].state == ERR)
		{
			if (pthread_mutex_lock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_LOCK));
			*philo->stop_all = 1;
			if (pthread_mutex_unlock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_UNLOCK));
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *philo)
{
	t_philo	*monitor;

	monitor = philo;
	while (1)
	{
		if (check_all_eaten(monitor) || check_death(monitor)
			|| check_error(monitor))
			break ;
	}
	return (philo);
}
