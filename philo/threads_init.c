/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:12:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 14:18:14 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	threads_init(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->t_list[data->p_num], NULL, &monitor, \
		&data->philo[0]) != 0)
		return (1);
	while (i < data->p_num)
	{
		if (pthread_create(&data->t_list[i], NULL, &philo, &data->philo[i])
			!= 0)
			return (1);
		i++;
	}
	i = 0;
	if (pthread_join(data->t_list[data->p_num], NULL) != 0)
	{
		return (1);
	}
	while (i < data->p_num)
	{
		if (pthread_join(data->t_list[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
