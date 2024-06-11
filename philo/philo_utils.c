/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:10:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:17:37 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timediff(struct timeval *t1, struct timeval *t2)
{
	return ((t1->tv_sec - t2->tv_sec) * 1000
		+ (t1->tv_usec - t2->tv_usec) / 1000);
}

long long	get_timestamp(t_philo *philo)
{
	gettimeofday(&philo->t_now, NULL);
	return (timediff(&philo->t_now, &philo->t_start));
}

int	write_lock(t_philo *philo, char *msg)
{
	if (pthread_mutex_lock(philo->death_lock) != 0)
		return (philo_error(philo, MUTEX_LOCK));
	if (!*philo->stop_all)
	{
		if (pthread_mutex_lock(philo->write_lock) != 0)
			return (philo_error(philo, MUTEX_LOCK));
		printf("%lli %i %s\n", get_timestamp(philo), philo->id, msg);
		if (pthread_mutex_unlock(philo->write_lock) != 0)
			return (philo_error(philo, MUTEX_UNLOCK));
	}
	if (pthread_mutex_unlock(philo->death_lock) != 0)
		return (philo_error(philo, MUTEX_UNLOCK));
	return (0);
}

static int	time_limit(t_philo *philo, long long limit, struct timeval *last)
{
	gettimeofday(&philo->t_now, NULL);
	if (timediff(&philo->t_now, last) >= limit)
		return (1);
	return (0);
}

int	t_wait(t_philo *philo, long long time)
{
	struct timeval	last;

	gettimeofday(&last, NULL);
	while (1)
	{
		if (pthread_mutex_lock(philo->death_lock) != 0)
			return (philo_error(philo, MUTEX_LOCK));
		if (*philo->stop_all)
		{
			if (pthread_mutex_unlock(philo->death_lock) != 0)
				return (philo_error(philo, MUTEX_UNLOCK));
			return (1);
		}
		if (pthread_mutex_unlock(philo->death_lock) != 0)
			return (philo_error(philo, MUTEX_UNLOCK));
		if (time_limit(philo, time, &last))
			return (0);
		usleep(50);
	}
	return (1);
}
