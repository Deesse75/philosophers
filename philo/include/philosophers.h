/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:14:30 by sadorlin          #+#    #+#             */
/*   Updated: 2023/02/04 00:07:36 by sadorlin         ###   ########.fr       */
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
	FORK=0,
	EAT,
	SLEEP,
	THINK,
};

typedef struct s_philo{
	int				id;
	long			last_meal;
	struct s_data	*link;
	pthread_t		phi;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
}t_philo;

typedef struct s_data{
	int				nb_philo;
	int				time_eat;
	int				time_die;
	int				time_sleep;
	int				nb_meal;
	int				dead;
	long			start;
	t_philo			chrono;
	pthread_mutex_t	*action;
	pthread_mutex_t	*get_time;
	struct s_philo	*philo;
}t_data;

typedef struct s_var{
	int		timer;
	int		t_die;
	int		nb_philo;
	int		i;
}t_var;

int		check_arg(int ac, char **av, t_data *dt);
int		fn_error(int num);
void	fn_destroy(t_data *dt);
void	fn_message(t_philo *philo, int num);
int		get_time(t_data *dt);
int		take_fork_l(t_philo *philo);
int		take_fork_r(t_philo *philo);
int		start_eat(t_philo *philo);
int		start_sleep(t_philo *philo);
int		simu_with_meal(t_philo *philo, int meal, int id, int i);
int		simu_without_meal(t_philo *philo, int id);
void	init_var(t_var *var, t_data *link);
int		init_philo(t_data *dt);
int		init_data(t_data *dt, int i);
void	*routine(void *philo);
void	*chrono(void *chrono);

#endif
