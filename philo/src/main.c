/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:34:44 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:35:15 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


static int	init_data(t_data *dt, int i)
{
	dt->message = malloc(sizeof(pthread_mutex_t));
	dt->time_t = malloc(sizeof(pthread_mutex_t));
	dt->philo = malloc(sizeof(t_philo) * dt->nb_philo);
	if (!dt->philo || !dt->time_t || !dt->message)
		return (fn_close(err_malloc, dt));
	if (pthread_mutex_init(dt->message, NULL) != 0)
		return (fn_close(err_mutex, dt));
	if (pthread_mutex_init(dt->time_t, NULL) != 0)
		return (fn_close(err_mutex, dt));
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
		usleep(3000);
	start_simu(p);
	return ((void *)ret);
}


static int	init_philo(t_data *dt)
{
	int	i;
	int	*ret;

	i = -1;
	gettimeofday(&dt->go, NULL);
	dt->start = dt->go.tv_sec * 1000 + dt->go.tv_usec / 1000;
	while (++i < dt->nb_philo)
	{
		if (pthread_create(&dt->philo[i].phil, NULL, routine, &dt->philo[i]) != 0)
			return (fn_close(err_phil, dt));
		usleep(2000);
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

int	main(int ac, char **av)
{
	t_data	dt;

	dt = (t_data){0};
	if (check_arg(ac, av, &dt) == -1)
		return (-1);
	if (init_data(&dt, -1) == -1)
		return (-1);
	if (init_philo(&dt) == -1)
		return (-1);
	//fn_destroy(&dt);
	return (0);
}