/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/02 22:32:53 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_childs(t_philo *philos, t_infos infos)
{
	size_t	i;

	if (infos.nb_philo == 1)
	{
		philos[0].process = fork();
		if (philos[0].process == -1)
			return (-1);
		if (!philos[0].process)
			alone(&philos[0]);
		else
			waitpid(philos[0].process, NULL, 0);
		close_sem(&philos[0].sem);
		exit(0);
	}
	i = 0;
	while (i < infos.nb_philo)
	{
		philos[i].process = fork();
		if (philos[i].process < 0)
			return (-1);
		if (!philos[i].process)
			routine(philos[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_infos			infos;
	t_philo			philos[MAX_PHILOS];
	t_semaphores	sem;

	if (ac < 5 || ac > 6)
		return (printf(RED BOLD ERR_0 RESET RED ERR_1 ERR_2 ERR_3 RESET), FAIL);
	infos.must_eat = (ac == 6);
	set_infos(&infos, av);
	sem = init_sem(infos);
	init_philos(philos, infos, sem);
	if (create_childs(philos, infos) == -1)
		return (err("one fork failed"), close_sem(&sem), kill_everyone(philos),
			FAIL);
	create_monitor(philos);
	return (wait_for_childs(infos.nb_philo, sem));
}
