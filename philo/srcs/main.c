/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 12:51:12 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_vars *v, t_infos infos)
{
	size_t	i;

	i = 0;
	while (i < infos.nb_philo)
	{
		if (pthread_create(&v->philos[i].thread, NULL, routine,
				&v->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&v->monitor, NULL, monitor, &v->philos) != 0)
		return (-1);
	return (0);
}

int	join_threads(t_vars *v, t_infos infos)
{
	size_t	i;

	i = 0;
	while (i < infos.nb_philo)
	{
		if (pthread_join(v->philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(v->monitor, NULL) != 0)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	t_infos	infos;
	t_vars	vars;

	if (ac < 5 || ac > 6)
		return (printf(RED BOLD ERR_0 RESET RED ERR_1 ERR_2 ERR_3 RESET), FAIL);
	infos.must_eat = (ac == 6);
	set_infos(&infos, av);
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
