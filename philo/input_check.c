/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:33:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/10 16:28:33 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char *s)
{
	while (*s)
	{
		if (*s > 57 || *s < 48)
			return (1);
		s++;
	}
	return (0);
}

static int	check_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(argv[i]))
			return (1);
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Argument Number.\n", 24);
		return (1);
	}
	if (check_argv(argc, argv))
	{
		write(2, "Error: Invalid Input.\n", 22);
		return (1);
	}
	return (0);
}
