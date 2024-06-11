/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:41:44 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:46:50 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void	*args)
{
	t_philo	*philo;

	philo = args;
	if (philo->id % 2)
		usleep(100);
	while (1)
	{
		if (pthread_mutex_lock(philo->death_lock) != 0)
			return (0);
		if (*philo->stop_all)
		{
			pthread_mutex_unlock(philo->death_lock);
			return (0);
		}
		if (pthread_mutex_unlock(philo->death_lock) != 0)
			return (0);
		states(philo);
		philo->state = (philo->state + 1) % 3;
	}
	return (0);
}
