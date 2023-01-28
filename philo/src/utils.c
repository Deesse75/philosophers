#include "../include/philosophers.h"

void    fn_mess(t_philo *philo, int num)
{
    struct timeval  tps;


    pthread_mutex_lock(philo->memo->action);
    gettimeofday(&tps, NULL);
    if (num == FORK)
        printf("%ld %d has taken a fork\n", (tps.tv_sec * 10000 + tps.tv_usec - (philo->memo->time_start.tv_sec * 10000 + philo->memo->time_start.tv_usec)), philo->id);
    else if (num == EAT)
        printf("%ld %d is eating\n", (tps.tv_sec * 10000 + tps.tv_usec - (philo->memo->time_start.tv_sec * 10000 + philo->memo->time_start.tv_usec)), philo->id);
    else if (num == SLEEP)
        printf("%ld %d is sleeping\n", (tps.tv_sec * 10000 + tps.tv_usec - (philo->memo->time_start.tv_sec * 10000 + philo->memo->time_start.tv_usec)), philo->id);
    else if (num == THINK)
        printf("%ld %d is thinking\n", (tps.tv_sec * 10000 + tps.tv_usec - (philo->memo->time_start.tv_sec * 10000 + philo->memo->time_start.tv_usec)), philo->id);
    else if (num == DEAD)
        printf("%ld %d died\n", (tps.tv_sec * 10000 + tps.tv_usec - (philo->memo->time_start.tv_sec * 10000 + philo->memo->time_start.tv_usec)), philo->id);
    pthread_mutex_unlock(philo->memo->action);
}