#include "../include/philosophers.h"

void    fn_message(t_philo *philo, int num)
{
    long int            timer;
    struct timeval      t;

    pthread_mutex_lock(philo->memo->message);
    gettimeofday(&t, NULL);
    timer = (t.tv_sec * 1000) + (t.tv_usec / 1000) - philo->memo->start;
    if (num == FORK)
        printf("%d %d has taken a fork\n", (int)timer, philo->id);
    else if (num == EAT)
        printf("%d %d is eating\n", (int)timer, philo->id);
    else if (num == SLEEP)
        printf("%d %d is sleeping\n", (int)timer, philo->id);
    else if (num == THINK)
        printf("%d %d is thinking\n", (int)timer, philo->id);
    else if (num == DEAD)
        printf("%d %d died\n", (int)timer, philo->id);
    pthread_mutex_unlock(philo->memo->message);
}

void    check_time(t_philo *philo)
{
    struct timeval      t;
    long int            timer;

    gettimeofday(&t, NULL);
    if (philo->last_meal > 0)
        timer = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - philo->last_meal;
    else
        timer = 0;
    if (timer > philo->memo->time_die * 1000)
    {
        fn_message(philo, DEAD);
        philo->memo->dead = -1;
        fn_destroy(philo->memo);
    }
}
