/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locked_getters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 03:51:45 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_philo_age(t_philo *p)
{
	return (get_ms() - p->start_time);
}

bool	is_eating(t_philo *philo)
{
	bool	is_eating;

	is_eating = philo->is_eating;
	return (is_eating);
}

bool	is_dead(t_philo *philo)
{
	bool	is_dead;

	is_dead = (get_ms() - philo->time_of_last_meal > philo->infos.time_to_die
			&& !philo->is_eating);
	return (is_dead);
}

size_t	get_last_meal(t_philo *p)
{
	size_t	last_meal;

	last_meal = p->time_of_last_meal;
	return (last_meal);
}
