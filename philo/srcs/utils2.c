/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 12:00:58 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead_monitor(t_philo philo)
{
	bool	is_dead;

	pthread_mutex_lock(philo.meal_lock);
	is_dead = (get_ms() - philo.time_of_last_meal > philo.infos.time_to_die
			&& !philo.is_eating);
	pthread_mutex_unlock(philo.meal_lock);
	return (is_dead);
}

bool	is_dead_routine(t_philo *p)
{
	pthread_mutex_lock(p->dead_lock);
	if (*(p->is_dead))
		return (pthread_mutex_unlock(p->dead_lock), 1);
	pthread_mutex_unlock(p->dead_lock);
	return (0);
}
