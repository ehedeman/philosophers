/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:02:32 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/02 14:11:38 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	assign_philo(char **args)
{
	t_philo	philo;

	philo.i = 0;
	philo.args = args[1];
	philo.number = ft_atoi(args[1]);
	philo.die = ft_atoi(args[2]);
	philo.eat =ft_atoi(args[3]);
	philo.sleep = ft_atoi(args[4]);
	philo.total_eat = ft_atoi(args[5]);
	philo.forks = philo.number;
	return (philo);
}