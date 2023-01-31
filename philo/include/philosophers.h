/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:34:05 by sadorlin          #+#    #+#             */
/*   Updated: 2023/01/22 12:34:09 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

enum e_error{
	nb_arg=-100,
	arg_vide,
	arg_negative,
	arg_no_int,
	arg_invalid,
	phil_null,
	err_malloc,
	err_mutex,
	err_phil,
	err_phil2,
};

enum e_syntaxe{
	PAIR=0,
	IMPAIR,
	ALIVE,
	DEAD,
	FORK,
	EAT,
	SLEEP,
	THINK,
};

typedef struct s_data{
	int				nb_philo;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				nb_meal;
	int				dead;
	int				start;
	struct timeval	go;
	pthread_mutex_t	*message;
	pthread_mutex_t	*time_t;
	struct s_philo	*philo;
}t_data;

typedef struct s_philo{
	int				id;
	int				state;
	t_data			*memo;
	int				last_meal;
	struct timeval	meal;
	pthread_t		phil;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
}t_philo;

int		check_arg(int ac, char **av, t_data *dt);
int		fn_error(int num);
int		fn_close(int num, t_data *dt);
void	fn_destroy(t_data *dt);
void    fn_message(t_philo *philo, int num);
void    check_time(t_philo *philo);
void	start_simu(t_philo *philo);

#endif