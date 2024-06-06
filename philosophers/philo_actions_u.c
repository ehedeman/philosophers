/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_u.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:02:07 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 14:59:36 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*function for checking if smbd died -> with mutex*/
int	check_for_death(t_philo *philo)
{
	pthread_mutex_lock(philo->d_lock);
	if (*philo->death == 1)
	{
		pthread_mutex_unlock(philo->d_lock);
		return (1);
	}
	else if (*philo->death == 0)
	{
		pthread_mutex_unlock(philo->d_lock);
		return (0);
	}
	return (0);
}

/*function for checking if this philo died*/
/*if time passed since last eat is bigger than time_to_die*/
/*then the philo dies*/
int	check_if_dead(t_philo *philo)
{
	gettimeofday(&philo->t_now, NULL);
	if (timediff(&philo->t_now, &philo->t_last_eat) >= philo->t_die)
	{
		philo->action = DIE;
		return (1);
	}
	return (0);
}

/*checks if everyone is done eating*/
int	check_a_d_e(t_philo *philo)
{
	pthread_mutex_lock(philo->e_c_lock);
	if (*philo->all_done_eating == 0)
	{
		pthread_mutex_unlock(philo->e_c_lock);
		*philo->stop_all = 1;
		return (1);
	}
	else if (*philo->all_done_eating > 0 || *philo->all_done_eating == -1)
	{
		pthread_mutex_unlock(philo->e_c_lock);
		return (0);
	}
	return (0);
}

/*checks if this philo is done eating*/
int	check_eat_count(t_philo *philo)
{
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(philo->e_c_lock);
		*philo->all_done_eating -= 1;
		pthread_mutex_unlock(philo->e_c_lock);
		philo->eat_count = -1;
		return (1);
	}
	return (0);
}

/*write protected pritnf*/
void	write_lock(t_philo *philo, char *msg)
{
	if (check_if_dead(philo) || check_a_d_e(philo) || check_for_death(philo))
		return ;
	pthread_mutex_lock(philo->write_lock);
	printf("%lli %i %s.\n", get_timestamp(philo), philo->index, msg);
	pthread_mutex_unlock(philo->write_lock);
}
