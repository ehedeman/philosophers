/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:39:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 16:14:19 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l->lock);
	pthread_mutex_lock(&philo->fork_r->lock);
	if (!philo->fork_l->in_use && !philo->fork_r->in_use)
	{
		// philo->fork_l->in_use = 1;
		// philo->fork_r->in_use = 1;
		pthread_mutex_unlock(&philo->fork_l->lock);
		pthread_mutex_unlock(&philo->fork_r->lock);
		return (1);
	}
	else if (philo->fork_l->in_use == 1 || philo->fork_r->in_use == 1)
	{
		pthread_mutex_unlock(&philo->fork_l->lock);
		pthread_mutex_unlock(&philo->fork_r->lock);
		return (0);
	}
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (check_if_dead(philo) || check_a_d_e(philo) || check_for_death(philo))
		return (1);
	pthread_mutex_lock(&philo->fork_l->lock);
	pthread_mutex_lock(&philo->fork_r->lock);
	philo->fork_r->in_use = 1;
	philo->fork_l->in_use = 1;
	pthread_mutex_unlock(&philo->fork_l->lock);
	pthread_mutex_unlock(&philo->fork_r->lock);
	return (0);
}

void	release_forks(t_philo *philo)
{
	if (check_if_dead(philo) || check_a_d_e(philo) || check_for_death(philo))
		return ;
	pthread_mutex_lock(&philo->fork_l->lock);
	pthread_mutex_lock(&philo->fork_r->lock);
	philo->fork_l->in_use = 0;
	philo->fork_r->in_use = 0;
	pthread_mutex_unlock(&philo->fork_l->lock);
	pthread_mutex_unlock(&philo->fork_r->lock);
}
