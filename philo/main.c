/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:51:31 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/11 15:28:05 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	time_check_one(long long time_limit, struct timeval *start)
{
	struct timeval	recent;

	gettimeofday(&recent, NULL);
	if (timediff(&recent, start) >= time_limit)
		return (1);
	return (0);
}

static void	one_philo(char **argv)
{
	struct timeval	start;
	struct timeval	last;

	gettimeofday(&start, NULL);
	write(1, "0 0 started thinking.\n", 22);
	while (1)
	{
		if (time_check_one((long long)atoi(argv[2]), &start))
			break ;
		usleep(100);
	}
	gettimeofday(&last, NULL);
	printf("%lli 0 has died.", timediff(&last, &start));
}

static t_data	*data_allocation(char **argv)
{
	t_data	*data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		data_error(data, ALLOCATION_ERR);
		return (0);
	}
	data->t_list = malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
	if (!data->t_list)
	{
		data_error(data, ALLOCATION_ERR);
		return (0);
	}
	return (data);
}

static int	end_sim(t_data *data)
{
	destroy_all(data);
	free_all(data);
	return (0);
}

// static void test(t_data *data)
// {
// 	int i = 0;
// 	while (i < data->p_num)
// 	{
// 		printf("%i eat_count: %i\n", data->philo[i].id,
// 			data->philo[i].eat_count);
// 		i++;
// 	}
// }

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (check_input(argc, argv))
		return (0);
	if (ft_atoi(argv[1]) == 1)
		one_philo(argv);
	else
	{
		data = data_allocation(argv);
		if (!data)
			return (0);
		else if (assign_data(data, argv, argc))
			data_error(data, MUTEX_INIT);
		else if (threads_init(data))
			data_error(data, THREAD_ERR);
		else if (end_sim(data))
			data_error(data, MUTEX_DESTROY);
	}
	return (0);
}
