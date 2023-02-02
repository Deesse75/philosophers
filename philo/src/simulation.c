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

int	simu_with_meal(t_philo *philo, int i)
{
	while (++i < philo->link->nb_meal && philo->link->dead == 0)
	{
		fn_message(philo, THINK);
		if (philo->id % 2 == 0)
		{
			if (take_fork_r(philo) == -1)
				return (-1);
		}
		else if (philo->id % 2 != 0)
			if (take_fork_l(philo) == -1)
				return (-1);
		if (start_eat(philo) == -1)
			return (-1);
		if (start_sleep(philo) == -1)
			return (-1);
	}
	philo->link->dead = -1;
	return (0);
}

int	simu_without_meal(t_philo *philo)
{
	while (philo->link->dead == 0)
	{
		if (philo->id % 2 == 0)
		{
			if (take_fork_r(philo) == -1)
				return (-1);
		}
		else if (philo->id % 2 != 0)
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
