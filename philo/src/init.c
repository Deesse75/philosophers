/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:35:47 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:36:42 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_mutex(t_data *dt)
{
	dt->philo = malloc(sizeof(t_philo) * dt->nb_philo);
	if (!dt->philo)
		return (fn_close(err_malloc, dt));
	dt->action = malloc(sizeof(pthread_mutex_t));
	if (!dt->action)
		return (fn_close(err_malloc, dt));
	if (pthread_mutex_init(dt->action, NULL) != 0)
		return (fn_close(err_mutex, dt));
	dt->fork = malloc(sizeof(pthread_mutex_t));
	if (!dt->fork)
		return (fn_close(err_malloc, dt));
	if (pthread_mutex_init(dt->fork, NULL) != 0)
		return (fn_close(err_mutex, dt));
	gettimeofday(&dt->time_start, NULL);
	return (0);
}

int	init_data(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < dt->nb_philo)
	{
		dt->philo[i].id = i + 1;
		dt->philo[i].state = ALIVE;
		dt->philo[i].memo = dt;
		if (pthread_mutex_init(&dt->philo[i].fork_r, NULL) != 0)
			return (fn_close(err_mutex, dt));
		if (i == dt->nb_philo - 1)
			dt->philo[i].fork_l = &dt->philo[0].fork_r;
		else
			dt->philo[i].fork_l = &dt->philo[i + 1].fork_r;
	}
	return (0);
}

static void	*routine(void *philo)
{
	t_philo	*p;
	int		*ret;

	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	*ret = 9;
	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(5);
	simul(p);
	return ((void *)ret);
}


int	init_philo(t_data *dt)
{
	int	i;
	int	*ret;

	i = -1;
	while (++i < dt->nb_philo)
	{
		if (pthread_create(&dt->philo[i].phil, NULL, routine, &dt->philo[i]) != 0)
			return (fn_close(err_phil, dt));
		usleep(100);
	}
	i = -1;
	while (++i < dt->nb_philo)
	{
		if (pthread_join(dt->philo[i].phil, (void *)&ret) != 0)
			return (fn_close(err_phil2, dt));
		if (*ret != 9)
			return (fn_close(err_mutex, dt));
		free(ret);
	}
	return (0);
}
