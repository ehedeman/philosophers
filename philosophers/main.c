/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:11:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 15:30:17 by ehedeman         ###   ########.fr       */
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
		usleep(50);
	}
	gettimeofday(&last, NULL);
	printf("%lli 0 has died.", timediff(&last, &start));
}

// static	void	test_all(t_data *data)
// {
// 	int i;	
// 	i = 0;
// 	while (i < data->p_number)
// 	{
// 		printf("%i:\n", data->philo[i].index);
// 		printf("how_many_times: %i\n", data->philo[i].eat_count);
// 		// printf("last_eat:%lli\n", data->philo[i].last_eat);
// 		// printf("fork %i: in_use: %i\n\n", i, data->forks[i].in_use);
// 		i++;
// 	}
// 		// printf("P_number:%i\n", data->p_number);
// 		// printf("start_time:%lli\n", data->start_time);
// 		printf("all_done_eating:%i\n", data->all_done_eating);
// 		// printf("has_died:%i\n", data->has_died);
// }


int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_input(argc, argv))
		return (0);
	if (ft_atoi(argv[1]) == 1)
		one_philo(argv);
	else
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (0);
		if (assign_data(data, argv, argc))
		{
			free_all(data, 1);
			return (0);
		}
		data->t_list = malloc(sizeof(pthread_t) * data->p_number);
		if (!data->t_list)
		{
			free_all(data, 1);
			return (0);
		}
		threads_init(data);
		//test_all(data);
		free_all(data, 0);
	}
}
