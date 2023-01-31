/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:38:49 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:41:45 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


static int	start_sleep(t_philo *philo)
{
    int i;

    i = 0;
    fn_message(philo, SLEEP);
    while (i < philo->memo->time_sleep)
    {
        usleep(1000);
        check_time(philo);
        i++;
    }
    return (0);
}

static int	start_eat(t_philo *philo)
{
    int i;

    i = 0;
    gettimeofday(&philo->meal, NULL);
    philo->last_meal = philo->meal.tv_sec * 1000 - philo->meal.tv_usec / 1000;
    fn_message(philo, EAT);
    while (i < philo->memo->time_eat)
    {
        usleep(1000);
        check_time(philo);
        i++;
    }
    return (0);
}

static void    drop_fork(t_philo * philo)
{
    pthread_mutex_unlock(&philo->fork_r);
    pthread_mutex_unlock(&philo->fork_r);
}

static void    take_fork(t_philo * philo)
{
    fn_message(philo, THINK);
    pthread_mutex_lock(&philo->fork_r);
    fn_message(philo, FORK);
    check_time(philo);
    pthread_mutex_lock(philo->fork_l);
    fn_message(philo, FORK);
    check_time(philo);
}

void start_simu(t_philo *philo)
{
    int i;
    int j;

    i = -1;
    if (philo->memo->nb_meal == -1)
        j = 1;
    else
    j = 0;
    while (++i <= philo->memo->nb_meal + j && philo->memo->dead == 0)
    {
        take_fork(philo);
        start_eat(philo);
        drop_fork(philo);
        start_sleep(philo);
        if (philo->memo->nb_meal == -1)
            j++;
    }
}
