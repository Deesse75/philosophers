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
    fn_mess(philo, SLEEP);

    usleep(philo->memo->time_sleep);

    return (0);
}

static int	start_eat(t_philo *philo)
{
    fn_mess(philo, THINK);
    pthread_mutex_lock(&philo->fork_r);
    fn_mess(philo, FORK);
    pthread_mutex_lock(philo->fork_l);
    fn_mess(philo, FORK);
    fn_mess(philo, EAT);

    usleep(philo->memo->time_eat);

    pthread_mutex_unlock(philo->fork_l);
    pthread_mutex_unlock(&philo->fork_r);

    return (0);
}

void simul(t_philo *philo)
{
    int i;

    i = -1;
    while (++i < 5)
    {
        start_eat(philo);
        start_sleep(philo);
    }
   // pthread_mutex_lock(philo->memo->action);
    printf("philo %d eat %d time\n\n", philo->id, i);
  //  pthread_mutex_unlock(philo->memo->action);


}