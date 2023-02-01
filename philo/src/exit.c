/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:36:52 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:37:33 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	fn_error(int num)
{
	if (num == nb_arg)
		write(2, "Error\nInvalid number of arguments.\n", 35);
	else if (num == arg_negative)
		write(2, "Error\nInvalid negative arguments.\n", 34);
	else if (num == arg_no_int)
		write(2, "Error\nInvalid int arguments.\n", 29);
	else if (num == arg_invalid)
		write(2, "Error\nInvalid digit characters.\n", 32);
	else if (num == arg_vide)
		write(2, "Error\nInvalid empty argument.\n", 30);
	else if (num == phil_null)
		write(2, "Error\nInvalid number of philosophers.\n", 38);
	else if (num == err_malloc)
		write(2, "Error\nMalloc() fail.\n", 21);
	else if (num == err_mutex)
		write(2, "Error\nMutex() fail.\n", 20);
	else if (num == err_phil)
		write(2, "Error\nPthread_create() fail.\n", 29);
	else if (num == err_phil2)
		write(2, "Error\nPthread_join() fail.\n", 27);
	return (-1);
}

void	fn_destroy(t_data *dt)
{
	int	i;

	i = -1;
	if (dt->message)
	{
		pthread_mutex_destroy(dt->message);
		free(dt->message);
	}
	if (dt->get_time)
	{
		pthread_mutex_destroy(dt->get_time);
		free(dt->get_time);
	}
	if (dt->philo)
	{
		while (++i < dt->nb_philo)
			pthread_mutex_destroy(&dt->philo[i].fork_r);
		free(dt->philo);
	}
}
