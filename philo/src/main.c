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

int	main(int ac, char **av)
{
	t_data	dt;

	dt = (t_data){0};
	if (check_arg(ac, av, &dt) == -1)
		return (-1);
	if (init_mutex(&dt) == -1)
		return (-1);
	if (init_data(&dt) == -1)
		return (-1);
	if (init_philo(&dt) == -1)
		return (-1);
	fn_destroy(&dt);
	return (0);
}
/*
fonction init :	-cree le philo
				-cree la fourchette
				-remplie les variables
				-envoi vers routine

fonction routine :	-lance la boucle (check, pense, check, eat, check, sleep)
					-check si philo vivant
					-check si nb de repas ok

fonction eat :	-si zero ou une fourchette => pense
				-message
				-si 2 fourchettes => mange
				-message

fonction sleep : 	-message
					-check
*/