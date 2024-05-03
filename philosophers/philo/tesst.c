/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tesst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:10:38 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/02 13:11:01 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine()
{
	printf("test\n");
	sleep(2);
	printf("test aber anders\n");
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;
	char		*test;

	if (argc != 6)
	{
		write(2, "Error.", 7);
		return (0);
	}
	test = argv[1];
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}