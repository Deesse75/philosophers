/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:37:50 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:38:22 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	fn_atoi(const char *src)
{
	long	val;
	int		i;

	i = 0;
	val = 0;
	if (src[i] == '\0')
		return (arg_vide);
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	if (src[i] == '+')
		i++;
	if (src[i] == '+')
		return (arg_invalid);
	while (src[i] >= '0' && src[i] <= '9')
	{
		val = (val * 10) + (src[i] - 48);
		if (val > 2147483647)
			return (fn_error(arg_no_int));
		i++;
	}
	return ((int)val);
}

static int	check_is_int(char **av, t_data *dt)
{
	dt->nb_philo = fn_atoi(av[1]);
	if (dt->nb_philo == 0)
		return (phil_null);
	if (dt->nb_philo < 0)
		return (dt->nb_philo);
	dt->time_die = fn_atoi(av[2]);
	if (dt->time_die < 0)
		return (dt->time_die);
	dt->time_eat = fn_atoi(av[3]);
	if (dt->time_eat < 0)
		return (dt->time_eat);
	dt->time_sleep = fn_atoi(av[4]);
	if (dt->time_sleep < 0)
		return (dt->time_sleep);
	if (av[5])
		dt->nb_meal = fn_atoi(av[5]);
	else
		dt->nb_meal = 0;
	if (dt->nb_meal < 0)
		return (dt->nb_meal);
	return (0);
}

static int	check_is_digit(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] == '-')
				return (arg_negative);
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (arg_invalid);
		}
	}
	return (0);
}

int	check_arg(int ac, char **av, t_data *dt)
{
	int	tp;

	if (ac != 5 && ac != 6)
		return (fn_error(nb_arg));
	tp = check_is_digit(av);
	if (tp != 0)
		return (fn_error(tp));
	tp = check_is_int(av, dt);
	if (tp != 0)
		return (fn_error(tp));
	return (0);
}
