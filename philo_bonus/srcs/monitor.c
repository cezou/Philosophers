/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:51:02 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 05:30:51 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_there_a_dead_philo(t_philo *p)
{
	sem_wait(p->sem.is_there_a_dead_lock);
	sem_post(p->sem.is_there_a_dead);
	if (errno == EOVERFLOW)
	{
		sem_post(p->sem.is_there_a_dead_lock);
		sem_wait(p->sem.is_dead_lock);
		p->is_dead = 1;
		sem_post(p->sem.is_dead_lock);
		return (1);
	}
	sem_wait(p->sem.is_there_a_dead);
	sem_post(p->sem.is_there_a_dead_lock);
	return (0);
}
void	kill_philo(t_philo *philo)
{
	sem_wait(philo->sem.is_dead_lock);
	philo->is_dead = 1;
	sem_post(philo->sem.is_dead_lock);
	sem_post(philo->sem.is_there_a_dead);
}

bool	is_philo_dead(t_philo *philo)
{
	if (!is_eating(philo) && get_ms()
		- get_last_meal(philo) > philo->infos.time_to_die)
		return (kill_philo(philo), 1);
	return (0);
}

bool	has_eaten(t_philo *philo)
{
	if (get_last_meal(philo) >= philo->infos.nb_times_must_eat)
		return (kill_philo(philo), 1);
	return (0);
}

void	check_dead_and_meals(t_philo *p)
{
	while (1)
	{
		if (is_philo_dead(p))
			break ;
		if (is_there_a_dead_philo(p))
			break ;
		if (has_eaten(p))
			break ;
	}
}

void	check_dead(t_philo *p)
{
	while (1)
	{
		if (is_philo_dead(p))
			break ;
		if (is_there_a_dead_philo(p))
			break ;
	}
}

void	*monitor(void *philosopher)
{
	t_philo *philo;

	philo = (t_philo *)philosopher;
	if (philo->infos.must_eat)
		check_dead_and_meals(philo);
	else
		check_dead(philo);
	return (NULL);
}