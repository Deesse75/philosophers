/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:14:50 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/02 11:17:19 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	start_sleep(t_philo *philo)
{
	long	t;

	t = get_time(philo->link);
	fn_message(philo, SLEEP);
	while ((get_time(philo->link) - t < philo->link->time_sleep)
		&& philo->link->dead == 0)
		usleep(1000);
	if (philo->link->dead == -1)
		return (-1);
	return (0);
}

int	start_eat(t_philo *philo)
{
	philo->last_meal = get_time(philo->link);
	fn_message(philo, EAT);
	while (get_time(philo->link) - philo->last_meal < philo->link->time_eat
		&& philo->link->dead == 0)
		usleep(100);
	pthread_mutex_unlock(&philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	return (0);
}

int	take_fork_r(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_r);
	fn_message(philo, FORK);
	if (philo->link->dead == -1)
	{
		pthread_mutex_unlock(&philo->fork_r);
		return (-1);
	}
	pthread_mutex_lock(philo->fork_l);
	fn_message(philo, FORK);
	if (philo->link->dead == -1)
	{
		pthread_mutex_unlock(&philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		return (-1);
	}
	return (0);
}

int	take_fork_l(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	fn_message(philo, FORK);
	if (philo->link->nb_philo == 1 || philo->link->dead == -1)
	{
		pthread_mutex_unlock(philo->fork_l);
		return (-1);
	}
	pthread_mutex_lock(&philo->fork_r);
	fn_message(philo, FORK);
	if (philo->link->dead == -1)
	{
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->fork_r);
		return (-1);
	}
	return (0);
}
