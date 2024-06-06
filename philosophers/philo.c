/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:41:44 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 16:01:22 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void	*args)
{
	t_philo	*philo;

	philo = args;
	philo->action = 0;
	while (!*philo->stop_all)
	
	{
		actions(philo);
		philo->action = (philo->action + 1) % 3;
	}
	return (NULL);
}
