/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:56:01 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:16:43 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	if (philo->is_eating == 1)
		return (0);
	gettimeofday(&philo->t_now, NULL);
	if (timediff(&philo->t_now, &philo->t_last_eat) >= philo->t_die)
		return (1);
	return (0);
}

void	write_monitor(t_philo *philo, char *msg)
{
	if (!msg)
		printf("Everyone has eaten the required amount of times.\n");
	else
		printf("%lli %i %s\n", get_timestamp(philo), philo->id, msg);
}
