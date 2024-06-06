/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:54:54 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 13:59:44 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data, int error)
{
	if (error == 1)
		write(2, "Error\n", 6);
	if (data)
	{
		if (data->t_list)
			free(data->t_list);
		free(data);
	}
}

static int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long	i;
	long	nbr;
	int		negative;

	i = 0;
	nbr = 0;
	negative = 1;
	while (str[i] != '\0' && (str[i] == 32 || str[i] == '\t'
			||str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f'))
		i++;
	if (str[i] != '\0' && str[i] == '-')
	{
		negative = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	nbr *= negative;
	return (nbr);
}
