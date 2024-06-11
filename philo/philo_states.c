/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:58:11 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/10 16:36:01 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	think(t_philo *philo)
{
	if (write_lock(philo, "is thinking") != 0)
		return (1);
	return (0);
}

static int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->fork_l) != 0)
		return (philo_error(philo, MUTEX_LOCK));
	write_lock(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->fork_r) != 0)
		return (philo_error(philo, MUTEX_LOCK));
	philo->is_eating = 1;
	write_lock(philo, "has taken a fork");
	gettimeofday(&philo->t_last_eat, NULL);
	write_lock(philo, "is eating");
	t_wait(philo, (long long) philo->t_eat);
	philo->is_eating = 0;
	if (pthread_mutex_unlock(philo->fork_l) != 0)
		return (philo_error(philo, MUTEX_UNLOCK));
	if (pthread_mutex_unlock(philo->fork_r) != 0)
		return (philo_error(philo, MUTEX_UNLOCK));
	if (philo->eat_count > 0)
		philo->eat_count--;
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	if (write_lock(philo, "is sleeping") != 0)
		return (1);
	if (t_wait(philo, (long long) philo->t_sleep) != 0)
		return (1);
	return (0);
}

int	states(t_philo *philo)
{
	if (philo->state == THINK)
		think(philo);
	else if (philo->state == EAT)
		eat(philo);
	else if (philo->state == SLEEP)
		ft_sleep(philo);
	if (philo->state == ERR)
	{
		while (1)
		{
			if (pthread_mutex_lock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_LOCK));
			if (*philo->stop_all)
			{
				if (pthread_mutex_unlock(philo->death_lock) != 0)
					return (philo_error(philo, MUTEX_UNLOCK));
				return (0);
			}
			if (pthread_mutex_unlock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_UNLOCK));
			usleep(10);
		}
	}
	return (0);
}
