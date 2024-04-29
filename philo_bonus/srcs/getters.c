/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:57:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 05:28:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_philo_age(t_philo *p)
{
	return (get_ms() - p->start_time);
}

size_t	get_last_meal(t_philo *p)
{
	size_t	last_meal;

	sem_wait(p->sem.meal_lock);
	last_meal = p->time_of_last_meal;
	sem_post(p->sem.meal_lock);
	return (last_meal);
}

size_t	get_meals(t_philo *p)
{
	size_t	nb_meals;

	sem_wait(p->sem.meal_lock);
	nb_meals = p->meals_eaten;
	sem_post(p->sem.meal_lock);
	return (nb_meals);
}

bool	is_eating(t_philo *philo)
{
	bool	is_eating;

	sem_wait(philo->sem.is_eating_lock);
	is_eating = philo->is_eating;
	sem_post(philo->sem.is_eating_lock);
	return (is_eating);
}

bool	is_dead(t_philo *philo)
{
	bool	is_dead;

	sem_wait(philo->sem.is_dead_lock);
	is_dead = philo->is_dead;
	sem_post(philo->sem.is_dead_lock);
	return (is_dead);
}
