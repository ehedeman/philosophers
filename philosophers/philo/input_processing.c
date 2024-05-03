/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:34:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/03 13:23:42 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void	*args)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = args;
	while (i < philo->number)
	{
		printf("Time Passed:%i\n", i);
		if (philo->forks > 1)
			sleep(philo->eat);
		else
			sleep(philo->sleep);
		i++;
	}
	return (0);
}

static void	*philos_init(t_philo *philo)
{
	int i;

	i = 0;
	while(i < philo->number)
	{
		pthread_create(&philo->t_list[i], NULL, &ft_philo, philo);
		i++;
	}
	i = 0;
	while (i < philo->number)
	{
		pthread_join(philo->t_list[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	if (argc != 6)
	{
		write(2, "Error: Argument Number\n", 6);
		return (0);
	}
	philo = assign_philo(argv);
	philo.t_list = malloc(sizeof(pthread_t) * philo.number);
	if (!philo.t_list)
		return (0);
	philos_init(&philo);
	free(philo.t_list);
	return (0);
}
