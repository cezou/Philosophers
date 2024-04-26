/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locked_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 18:26:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_philo_age(t_philo *p)
{
	size_t	philo_age;

	pthread_mutex_lock(p->meal_lock);
	philo_age = get_ms() - p->start_time;
	pthread_mutex_unlock(p->meal_lock);
	return (philo_age);
}

bool	is_eating(t_philo *philo)
{
	bool	is_eating;

	pthread_mutex_lock(philo->is_eating_lock);
	is_eating = philo->is_eating;
	pthread_mutex_unlock(philo->is_eating_lock);
	return (is_eating);
}

bool	is_dead_monitor(t_philo *philo)
{
	bool	is_dead;

	pthread_mutex_lock(philo->meal_lock);
	is_dead = (get_ms() - philo->time_of_last_meal > philo->infos.time_to_die
			&& !is_eating(philo));
	pthread_mutex_unlock(philo->meal_lock);
	return (is_dead);
}

bool	is_dead_routine(t_philo *p)
{
	bool	is_dead;

	pthread_mutex_lock(p->dead_lock);
	is_dead = *(p->is_dead);
	pthread_mutex_unlock(p->dead_lock);
	return (is_dead);
}

size_t	get_last_meal(t_philo *p)
{
	size_t	last_meal;

	pthread_mutex_lock(p->meal_lock);
	last_meal = p->time_of_last_meal;
	pthread_mutex_unlock(p->meal_lock);
	return (last_meal);
}
