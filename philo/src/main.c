/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:17:44 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/02 11:18:22 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*chrono(void *chrono)
{
	t_philo	*c;
	int		i;

	i = 0;
	c = (t_philo *)chrono;
	while (i < c->link->nb_philo && c->link->dead == 0)
	{
		pthread_mutex_lock(c->link->message);
		if (get_time(c->link) - c->link->philo[i].last_meal >= c->link->time_die
			&& c->link->dead == 0)
		{
			c->link->dead = -1;
			printf("%ld %d died\n", get_time(c->link) - c->link->start, c->link->philo[i].id);
			usleep(100);
		}
		pthread_mutex_unlock(c->link->message);
		i++;
		if (i == c->link->nb_philo)
			i = 0;
	}
	return (NULL);
}

static int	init_data(t_data *dt, int i)
{
	dt->message = malloc(sizeof(pthread_mutex_t));
	dt->get_time = malloc(sizeof(pthread_mutex_t));
	dt->philo = malloc(sizeof(t_philo) * dt->nb_philo);
	if (!dt->philo || !dt->get_time || !dt->message)
		return (fn_error(err_malloc));
	if (pthread_mutex_init(dt->message, NULL) != 0)
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

static void	*routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		usleep(3000);
	p->last_meal = p->link->start;
	if (p->link->nb_meal == -1)
		simu_without_meal(philo);
	else
		simu_with_meal(philo, -1);
	return (NULL);
}

static int	init_philo(t_data *dt)
{
	int	i;

	i = -1;
	dt->start = get_time(dt);
	while (++i < dt->nb_philo)
	{
		if (pthread_create(&dt->philo[i].phi, NULL, routine, &dt->philo[i]) != 0)
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
