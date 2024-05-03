/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 11:06:23 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_infos	infos;
	t_vars	vars;

	if (ac < 5 || ac > 6)
		return (printf(RED ERR_0 RESET RRED ERR_1 ERR_2 ERR_3 RESET), FAIL);
	infos.must_eat = (ac == 6);
	set_infos(&infos, av);
	if (infos.nb_philo == 1)
		return (create_alone(infos));
	if (init_philos(&vars, infos) == -1)
		return (err(T_ERR_0), FAIL);
	if (create_threads(&vars, infos) == -1)
		return (err(T_ERR_1), destroy_all_mutexes(&vars, vars.forks,
				infos.nb_philo), FAIL);
	if (join_threads(&vars, infos) == -1)
		return (err(T_ERR_2), destroy_all_mutexes(&vars, vars.forks,
				infos.nb_philo), FAIL);
	destroy_all_mutexes(&vars, vars.forks, infos.nb_philo);
}
