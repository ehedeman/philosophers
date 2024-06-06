/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timestamps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:49:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 14:06:47 by ehedeman         ###   ########.fr       */
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
	return (timediff(&philo->t_now, philo->t_start));
}
