/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:58:11 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/06 16:24:51 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	long long	wait_time;

	write_lock(philo, "is thinking");
	gettimeofday(&philo->t_now, NULL);
	wait_time = timediff(&philo->t_now, &philo->t_last_eat) - \
		(long long) philo->t_eat;
	if (philo->p_num > 2 && philo->has_eaten)
		t_wait(philo, (long long) philo->t_eat + 1 - wait_time);
}

static void	eat(t_philo *philo)
{
	while (!try_take_forks(philo))
	{
		if (check_if_dead(philo) || check_a_d_e(philo)
			|| check_for_death(philo))
			return ;
		usleep(100);
	}
	take_forks(philo);
	write_lock(philo, "has taken a fork");
	write_lock(philo, "has taken a fork");
	gettimeofday(&philo->t_last_eat, NULL);
	write_lock(philo, "is eating");
	t_wait(philo, (long long) philo->t_eat);
	release_forks(philo);
	if (philo->eat_count > 0)
		philo->eat_count--;
	philo->has_eaten = 1;
	check_eat_count(philo);
}

static void	ft_sleep(t_philo *philo)
{
	write_lock(philo, "is sleeping");
	t_wait(philo, philo->t_sleep);
}

/*wenn schon jemand anders gestorben ist, aka philo->death is schon 1,
dann stop*/
static void	die(t_philo *philo)
{
	if (check_for_death(philo))
		return ;
	pthread_mutex_lock(philo->d_lock);
	*philo->death = 1;
	*philo->stop_all = 1;
	pthread_mutex_unlock(philo->d_lock);
	printf("%lli %i has died.", get_timestamp(philo), philo->index);
}

int	actions(t_philo *philo)
{
	if (check_if_dead(philo) || check_a_d_e(philo) || check_for_death(philo))
		return (0);
	if (philo->action == THINK)
		think(philo);
	else if (philo->action == EAT)
		eat(philo);
	else if (philo->action == SLEEP)
		ft_sleep(philo);
	if (philo->action == DIE)
		die(philo);
	return (0);
}
