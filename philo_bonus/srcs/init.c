/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 03:05:28 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_value_or_exit(long int entry, size_t *nb)
{
	if (entry == -1)
	{
		printf(RED BOLD "ERROR: " RESET RED ERR_NB RESET);
		exit(FAIL);
	}
	*nb = entry;
}

void	set_infos(t_infos *infos, char **av)
{
	set_value_or_exit(atoi_is_unsignedint(av[1]), &infos->nb_philo);
	if (infos->nb_philo > 200)
		(printf(RED BOLD "ERROR: " RESET RED "Too much philos (> 200)\n" RESET),
			exit(FAIL));
	set_value_or_exit(atoi_is_unsignedint(av[2]), &infos->time_to_die);
	set_value_or_exit(atoi_is_unsignedint(av[3]), &infos->time_to_eat);
	set_value_or_exit(atoi_is_unsignedint(av[4]), &infos->time_to_sleep);
	if (infos->must_eat)
		set_value_or_exit(atoi(av[5]), &infos->nb_times_must_eat);
	infos->start_time = 0;
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
