/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:18:27 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/02 11:18:46 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	simu_with_meal(t_philo *philo, int meal, int id, int i)
{
	pthread_mutex_lock(philo->link->action);
	id = philo->id;
	pthread_mutex_unlock(philo->link->action);
	while (++i < meal)
	{
		if (id % 2 == 0)
		{
			if (take_fork_r(philo) == -1)
				return (-1);
		}
		else
		{
			if (take_fork_l(philo) == -1)
				return (-1);
		}
		if (start_eat(philo) == -1)
			return (-1);
		if (start_sleep(philo) == -1)
			return (-1);
		fn_message(philo, THINK);
	}
	pthread_mutex_lock(philo->link->action);
	philo->link->dead = -1;
	pthread_mutex_unlock(philo->link->action);
	return (0);
}

int	simu_without_meal(t_philo *philo, int id)
{
	pthread_mutex_lock(philo->link->action);
	id = philo->id;
	pthread_mutex_unlock(philo->link->action);
	while (1)
	{
		if (id % 2 == 0)
		{
			if (take_fork_r(philo) == -1)
				return (-1);
		}
		else
		{
			if (take_fork_l(philo) == -1)
				return (-1);
		}
		if (start_eat(philo) == -1)
			return (-1);
		if (start_sleep(philo) == -1)
			return (-1);
		fn_message(philo, THINK);
	}
	return (0);
}
