/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 02:53:30 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/19 00:34:12 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// si get_ms - last_meal >= time_to_die: dead (dead lock)
// si chacun des philos a mange au moins meal nb_times_must_eat (meal lock)

static void	kill_philos(t_philo *philo, bool there_is_a_dead)
{
	if (there_is_a_dead)
		locked_print(RED "died" RESET, philo);
	pthread_mutex_lock(philo->dead_lock);
	*(philo->is_dead) = 1;
	pthread_mutex_unlock(philo->dead_lock);
}

void	search_for_dead_philo(t_philo *philos)
{
	size_t	i;

	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < philos->infos.nb_philo)
		{
			if (is_dead_monitor(&philos[i]))
				return (kill_philos(&philos[i], 1));
			i++;
		}
	}
}

bool	has_eaten(t_philo *philo, t_infos infos)
{
	bool	has_eaten;

	pthread_mutex_lock(philo->meal_lock);
	has_eaten = philo->meals_eaten >= infos.nb_times_must_eat;
	pthread_mutex_unlock(philo->meal_lock);
	return (has_eaten);
}

void	check_dead_and_meals(t_philo *philos, t_infos infos)
{
	size_t	i;
	bool	everyone_has_eaten;

	while (1)
	{
		usleep(1000);
		i = 0;
		everyone_has_eaten = 1;
		while (i < infos.nb_philo)
		{
			if (is_dead_monitor(&philos[i]))
				return (kill_philos(&philos[i], 1));
			if (everyone_has_eaten && !has_eaten(&philos[i], infos))
				everyone_has_eaten = 0;
			i++;
		}
		if (everyone_has_eaten)
			return (kill_philos(&philos[0], 0));
	}
}

void	*monitor(void *philosophers)
{
	t_philo	*philos;

	philos = (t_philo *)philosophers;
	usleep(philos->infos.nb_philo * 500);
	if (philos->infos.must_eat)
		check_dead_and_meals(philos, philos[0].infos);
	else
		search_for_dead_philo(philos);
	return (NULL);
}
