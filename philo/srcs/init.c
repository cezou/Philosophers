/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 11:20:27 by cviegas          ###   ########.fr       */
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
	if (infos->nb_philo > 200 || infos->nb_philo == 0)
		(printf(RED "ERROR: " RESET RRED "Philo number != ]0;200]\n" RESET),
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
				exit(0));
	}
	infos->start_time = 0;
}

void	set_philos_data(t_vars *v, t_infos infos, pthread_mutex_t *forks)
{
	size_t	i;

	i = 0;
	v->dead_flag = 0;
	while (i < infos.nb_philo)
	{
		v->philos[i].infos = infos;
		v->philos[i].time_of_last_meal = 0;
		v->philos[i].id = i + 1;
		v->philos[i].meals_eaten = 0;
		v->philos[i].is_eating = 0;
		v->philos[i].is_dead = &v->dead_flag;
		v->philos[i].dead_lock = &v->dead_lock;
		v->philos[i].meal_lock = &v->meal_lock;
		v->philos[i].write_lock = &v->write_lock;
		v->philos[i].is_eating_lock = &v->is_eating_lock;
		v->philos[i].fork[LEFT] = &forks[i];
		if (i != infos.nb_philo - 1)
			v->philos[i].fork[RIGHT] = &forks[i + 1];
		else
			v->philos[i].fork[RIGHT] = &forks[0];
		i++;
	}
}

int	init_philos(t_vars *v, t_infos infos)
{
	if (init_mutexes(v, v->forks, infos.nb_philo) == -1)
		return (-1);
	set_philos_data(v, infos, v->forks);
	return (0);
}
