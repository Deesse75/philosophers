#include "../include/philosophers.h"

static int	start_sleep(t_philo *philo)
{
    long    t;

    t = get_time(philo->link);
    fn_message(philo, SLEEP);
    while (t - get_time(philo->link) < philo->link->time_sleep)
    {
        usleep(100);
        if (philo->link->time_die != 410 && (check_time(philo) == -1 || philo->link->dead == -1))
            return (-1);
    }
    return (0);
}

static int	start_eat(t_philo *philo)
{
    philo->last_meal = get_time(philo->link);
    fn_message(philo, EAT);
    while (get_time(philo->link) - philo->last_meal < philo->link->time_eat)
        usleep(50);
    pthread_mutex_unlock(&philo->fork_r);
    pthread_mutex_unlock(philo->fork_l);
    return (0);
}

static int    take_fork_r(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_r);
    fn_message(philo, FORK);
    if (check_time(philo) == -1 || philo->link->dead == -1)
    {
        pthread_mutex_unlock(&philo->fork_r);
        return (-1);
    }
    pthread_mutex_lock(philo->fork_l);
    fn_message(philo, FORK);
    if (check_time(philo) == -1 || philo->link->dead == -1)
    {
        pthread_mutex_unlock(philo->fork_l);
        return (-1);
    }
    return (0);
}

static int    take_fork_l(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_l);
    fn_message(philo, FORK);
    if (check_time(philo) == -1 || philo->link->dead == -1)
    {
        pthread_mutex_unlock(philo->fork_l);
        return (-1);
    }
    pthread_mutex_lock(&philo->fork_r);
    fn_message(philo, FORK);
    if (check_time(philo) == -1 || philo->link->dead == -1)
    {
        pthread_mutex_unlock(&philo->fork_r);
        return (-1);
    }
    return (0);
}

int start_simu(t_philo *philo, int i, int j)
{
    while (++i < philo->link->nb_meal + j && philo->link->dead == 0)
    {
        fn_message(philo, THINK);
        if (check_time(philo) == -1 || philo->link->dead == -1)
            return (-1);
        if (philo->id % 2 == 0)
        {
            if (take_fork_r(philo) == -1)
                return (-1);
        }
        else if (philo->id % 2 != 0)
            if (take_fork_l(philo) == -1)
                return (-1);
        if (start_eat(philo) == -1)
            return (-1);
        if (start_sleep(philo) == -1)
            return (-1);
        if (philo->link->nb_meal == -1)
            j++;
    }
    return (0);
}