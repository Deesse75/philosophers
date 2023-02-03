/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:18:51 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/04 00:14:55 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	fn_message(t_philo *philo, int num)
{
	long	timer;

	pthread_mutex_lock(philo->link->action);
	timer = get_time(philo->link) - philo->link->start;
	if (philo->link->dead == 0 && num == FORK)
		printf("\033[36m%ld %d has taken a fork\033[0m\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == EAT)
		printf("\033[1;31m%ld %d is eating\033[0m\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == SLEEP)
		printf("%ld %d is sleeping\n", timer, philo->id);
	else if (philo->link->dead == 0 && num == THINK)
		printf("%ld %d is thinking\n", timer, philo->id);
	pthread_mutex_unlock(philo->link->action);
}

int	get_time(t_data *dt)
{
	struct timeval	t;

	pthread_mutex_lock(dt->get_time);
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(dt->get_time);
	return ((int)(t.tv_sec * 1000 + t.tv_usec / 1000));
}
