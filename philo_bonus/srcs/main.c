/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 07:15:50 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_childs(t_philo *philos, t_infos infos)
{
	size_t	i;

	i = 0;
	while (i < infos.nb_philo)
	{
		philos[i].process = fork();
		if (philos[i].process < 0)
			return (-1);
		if (!philos[i].process)
			routine(&philos[i]);
		i++;
	}
	return (0);
}

int	wait_for_the_end(t_philo *philos)
{
	int		dead_philo_id;
	size_t	i;

	waitpid(-1, &dead_philo_id, 0);
	print(RED " died" RESET, &philos[dead_philo_id - 1]);
	i = 0;
	while (i < philos[0].infos.nb_philo)
	{
		if ((int)philos[i].id != dead_philo_id)
			kill(philos[i].process, SIGKILL);
		i++;
	}
	sem_close(philos[0].forks);
	sem_unlink("/sem_" SEM_NAME);
	return (0);
}

int	main(int ac, char **av)
{
	t_infos	infos;
	t_philo	philos[MAX_PHILOS];
	sem_t	*forks;

	if (ac < 5 || ac > 6)
		return (printf(RED BOLD ERR_0 RESET RED ERR_1 ERR_2 ERR_3 RESET), FAIL);
	infos.must_eat = (ac == 6);
	set_infos(&infos, av);
	forks = sem_open(SEM_NAME, O_CREAT, 0644, infos.nb_philo);
	if (!forks)
		return (err("sem_open failed"), FAIL);
	init_philos(philos, infos, forks);
	if (create_childs(philos, infos) == -1)
		return (err("one fork failed"), sem_close(forks), FAIL);
	return (wait_for_the_end(philos));
}
