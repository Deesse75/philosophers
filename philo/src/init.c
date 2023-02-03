/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 00:04:46 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/04 00:12:43 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_data(t_data *dt, int i)
{
	dt->action = malloc(sizeof(pthread_mutex_t));
	dt->get_time = malloc(sizeof(pthread_mutex_t));
	dt->philo = malloc(sizeof(t_philo) * dt->nb_philo);
	if (!dt->philo || !dt->get_time || !dt->action)
		return (fn_error(err_malloc));
	if (pthread_mutex_init(dt->action, NULL) != 0)
		return (fn_error(err_mutex));
	if (pthread_mutex_init(dt->get_time, NULL) != 0)
		return (fn_error(err_mutex));
	dt->chrono.link = dt;
	while (++i < dt->nb_philo)
	{
		dt->philo[i].id = i + 1;
		dt->philo[i].link = dt;
		if (pthread_mutex_init(&dt->philo[i].fork_r, NULL) != 0)
			return (fn_error(err_mutex));
		if (i == dt->nb_philo - 1)
			dt->philo[i].fork_l = &dt->philo[0].fork_r;
		else
			dt->philo[i].fork_l = &dt->philo[i + 1].fork_r;
	}
	return (0);
}

int	init_philo(t_data *dt)
{
	int	i;
	int	nb_philo;

	i = -1;
	pthread_mutex_lock(dt->action);
	nb_philo = dt->nb_philo;
	dt->start = get_time(dt);
	pthread_mutex_unlock(dt->action);
	while (++i < nb_philo)
	{
		if (pthread_create(
				&dt->philo[i].phi, NULL, routine, &dt->philo[i]) != 0)
			return (fn_error(err_phil));
		usleep(3000);
	}
	if (pthread_create(&dt->chrono.phi, NULL, chrono, &dt->chrono) != 0)
		return (fn_error(err_phil));
	i = -1;
	while (++i < dt->nb_philo)
	{
		if (pthread_join(dt->philo[i].phi, NULL) != 0)
			return (fn_error(err_phil2));
	}
	if (pthread_join(dt->chrono.phi, NULL) != 0)
		return (fn_error(err_phil2));
	return (0);
}

void	init_var(t_var *var, t_data *link)
{
	var->i = -1;
	var->nb_philo = link->nb_philo;
	var->t_die = link->time_die;
}
