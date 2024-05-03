/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 10:32:27 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_value_or_exit(long int entry, size_t *nb)
{
	if (entry == -1)
	{
		printf(RED "ERROR: " RESET RRED ERR_NB RESET);
		exit(FAIL);
	}
	*nb = entry;
}

void	set_infos(t_infos *infos, char **av)
{
	set_value_or_exit(atoi_is_unsignedint(av[1]), &infos->nb_philo);
	if (infos->nb_philo > 200)
		(printf(RED "ERROR: " RESET RRED "Too much philos (> 200)\n" RESET),
			exit(FAIL));
	set_value_or_exit(atoi_is_unsignedint(av[2]), &infos->time_to_die);
	set_value_or_exit(atoi_is_unsignedint(av[3]), &infos->time_to_eat);
	set_value_or_exit(atoi_is_unsignedint(av[4]), &infos->time_to_sleep);
	if (infos->must_eat)
	{
		set_value_or_exit(atoi_is_unsignedint(av[5]),
			&infos->nb_times_must_eat);
		if (infos->nb_times_must_eat == 0)
			(printf(GREEN "Success: " RESET "Philos don't have to eat\n"),
				exit(EXIT_SUCCESS));
	}
	infos->start_time = 0;
}

static void	set_null_sem(t_semaphores *sem)
{
	(sem_unlink("/sem_" SEM_NAME), sem_unlink("/sem_everyone_ate_" SEM_NAME),
		sem_unlink("/sem_there_is_a_dead_" SEM_NAME),
		sem_unlink("/sem_someone_died_" SEM_NAME),
		sem_unlink("/sem_start_" SEM_NAME));
	sem->forks = NULL;
	sem->everyone_ate = NULL;
	sem->there_is_a_dead = NULL;
	sem->someone_died = NULL;
	sem->start = NULL;
}

t_semaphores	init_sem(t_infos infos)
{
	t_semaphores	sem;

	set_null_sem(&sem);
	sem.forks = sem_open("/sem_" SEM_NAME, O_CREAT, 0644, infos.nb_philo);
	sem.everyone_ate = sem_open("/sem_everyone_ate_" SEM_NAME, O_CREAT, 0644,
			infos.nb_philo);
	sem.there_is_a_dead = sem_open("/sem_there_is_a_dead_" SEM_NAME, O_CREAT,
			0644, infos.nb_philo);
	sem.someone_died = sem_open("/sem_someone_died_" SEM_NAME, O_CREAT, 0644,
			1);
	if (!sem.forks || !sem.everyone_ate || !sem.there_is_a_dead
		|| !sem.someone_died)
		(err("sem_open failed"), close_sem(&sem), exit(FAIL));
	return (sem);
}

int	init_philos(t_philo *philos, t_infos infos, t_semaphores sem)
{
	size_t	start_time;
	size_t	i;

	i = 0;
	start_time = get_ms();
	while (i < infos.nb_philo)
	{
		philos[i].infos = infos;
		philos[i].sem = sem;
		philos[i].time_of_last_meal = 0;
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].is_eating = 0;
		philos[i].is_dead = 0;
		philos[i].start_time = start_time;
		i++;
	}
	return (0);
}
