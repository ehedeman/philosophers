/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:35:51 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/03 11:57:22 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_philo
{
	pthread_t	*t_list;
	char		*args;
	int		forks;
	int		number;
	int		die;
	int		eat;
	int		sleep;
	int		total_eat;
	int		i;
}				t_philo;

typedef struct	s_data
{
}				t_data;

typedef struct	s_pgrogramm
{
	t_philo	philosophers[300];
}				t_programm;

int	ft_atoi(const char *str);
t_philo	assign_philo(char **args);

