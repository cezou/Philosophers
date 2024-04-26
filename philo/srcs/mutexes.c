/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/25 05:56:47 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutex(pthread_mutex_t *__attr)
{
	pthread_mutex_destroy(__attr);
}

bool	init_mutex(pthread_mutex_t *__mutex)
{
	if (pthread_mutex_init(__mutex, NULL) != 0)
		return (0);
	return (1);
}

void	destroy_all_mutexes(t_vars *v, pthread_mutex_t *forks,
		size_t nb_crampted)
{
	size_t	i;

	destroy_mutex(&v->write_lock);
	destroy_mutex(&v->dead_lock);
	destroy_mutex(&v->meal_lock);
	i = 0;
	while (i < nb_crampted)
		destroy_mutex(&forks[i++]);
}

int	init_mutexes(t_vars *v, pthread_mutex_t *forks, size_t nb_philos)
{
	int	i;

	if (!init_mutex(&v->write_lock))
		return (-1);
	if (!init_mutex(&v->dead_lock))
		return (destroy_mutex(&v->write_lock), -1);
	if (!init_mutex(&v->meal_lock))
		return (destroy_mutex(&v->write_lock), destroy_mutex(&v->dead_lock),
			-1);
	i = -1;
	while (++i < (int)nb_philos)
		if (!init_mutex(&forks[i]))
			return (destroy_all_mutexes(v, forks, i), -1);
	return (0);
}
