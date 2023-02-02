#include "../include/philosophers.h"

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
	int		i;

	p = (t_philo *)philo;
	if (p->link->nb_meal == -1)
		i = 2;
	else
        i = 0;
	if (p->id % 2 == 0)
		usleep(3000);
	p->last_meal = p->link->start;
	start_simu(p, -1, i);
	return (NULL);
}

static int	init_philo(t_data *dt)
{
	int	i;
	int	*ret;

	i = -1;
	dt->start = get_time(dt);
	while (++i < dt->nb_philo)
	{
		if (pthread_create(&dt->philo[i].phi, NULL, routine, &dt->philo[i]) != 0)
			return (fn_error(err_phil));
		usleep(3000);
	}
	i = -1;
	while (++i < dt->nb_philo)
	{
		if (pthread_join(dt->philo[i].phi, (void *)&ret) != 0)
			return (fn_error(err_phil2));
	}
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