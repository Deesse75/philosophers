/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:18:51 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/02 11:19:24 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	fn_message(t_philo *philo, int num)
{
	long	timer;

	pthread_mutex_lock(philo->link->message);
	timer = get_time(philo->link) - philo->link->start;
	if (philo->link->dead == 0 && num == FORK)
		printf("%ld %d has taken a fork\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == EAT)
		printf("%ld %d is eating\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == SLEEP)
		printf("%ld %d is sleeping\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == THINK)
		printf("%ld %d is thinking\n", timer, philo->id);
	pthread_mutex_unlock(philo->link->message);
}
/*
int	check_time(t_philo *philo)
{
	if (philo->link->dead == 0 && get_time(philo->link) - philo->last_meal > philo->link->time_die)
	{
		pthread_mutex_lock(philo->link->message);
		philo->link->dead = -1;
		printf("%ld %d died\n", get_time(philo->link) - philo->link->start, philo->id);
		usleep(100);
		pthread_mutex_unlock(philo->link->message);
		return (-1);
	}
	return (0);
}
*/
int	get_time(t_data *dt)
{
	struct timeval	t;

	pthread_mutex_lock(dt->get_time);
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(dt->get_time);
	return ((int)(t.tv_sec * 1000 + t.tv_usec / 1000));
}
/*
void	lonely(t_philo *philo)
{
	while (get_time(philo->link) - philo->link->start < philo->link->time_die)
		usleep(100);
	printf("%ld %d died\n", get_time(philo->link) - philo->link->start, philo->id);
}
*/
