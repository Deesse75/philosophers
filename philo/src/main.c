/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:17:44 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/04 00:17:38 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*chrono(void *chrono)
{
	t_philo	*c;
	t_var	var;

	c = (t_philo *)chrono;
	var = (t_var){0};
	pthread_mutex_lock(c->link->action);
	init_var(&var, c->link);
	pthread_mutex_unlock(c->link->action);
	while (++var.i < var.nb_philo)
	{
		pthread_mutex_lock(c->link->action);
		var.timer
			= var.t_die - (get_time(c->link) - c->link->philo[var.i].last_meal);
		if (var.timer <= 0 && c->link->dead == 0)
		{
			c->link->dead = -1;
			printf("\033[33m%ld %d died\033[0m\n",
				get_time(c->link) - c->link->start, c->link->philo[var.i].id);
			pthread_mutex_unlock(c->link->action);
			return (NULL);
		}
		pthread_mutex_unlock(c->link->action);
		usleep(var.t_die / 8 * 1000);
		if (var.i == var.nb_philo - 1)
			var.i = -1;
		pthread_mutex_lock(c->link->action);
		if (c->link->dead == -1)
		{
			pthread_mutex_unlock(c->link->action);
			return (NULL);
		}
		pthread_mutex_unlock(c->link->action);
	}
	return (NULL);
}

void	*routine(void *philo)
{
	t_philo	*p;
	long	meal;
	int		id;

	p = (t_philo *)philo;
	pthread_mutex_lock(p->link->action);
	p->last_meal = p->link->start;
	meal = p->link->nb_meal;
	id = p->id;
	pthread_mutex_unlock(p->link->action);
	if (id % 2 == 0)
		usleep(4000);
	if (meal == -1)
		simu_without_meal(philo, 0);
	else
		simu_with_meal(philo, meal, 0, -1);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	dt;

	dt = (t_data){0};
	if (check_arg(ac, av, &dt) == -1
		|| init_data(&dt, -1) == -1
		|| init_philo(&dt) == -1)
		fn_destroy(&dt);
	fn_destroy(&dt);
	return (0);
}
