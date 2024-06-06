/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:12:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 14:19:45 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threads_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->p_number)
	{
		if (pthread_create(&data->t_list[i], NULL, &philo, &data->philo[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->p_number)
	{
		if (pthread_join(data->t_list[i], NULL))
			return (0);
		i++;
	}
	if (data->all_done_eating == 0)
	{
		printf("Everyone ate the required amount of times.\n");
		printf("Simulation stopped.\n");
	}
	return (0);
}
