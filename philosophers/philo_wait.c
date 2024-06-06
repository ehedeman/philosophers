/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:42:30 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 15:53:20 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (!check_a_d_e(philo) && !check_for_death(philo))
	{
		if (check_if_dead(philo))
			return (1);
		if (time_limit(philo, time, &last))
			return (0);
		usleep(100);
	}
	return (1);
}
