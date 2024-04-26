/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:51:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 22:36:57 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_if_not_dead(t_philo *p, size_t time_to_sleep_ms, bool can_die)
{
	size_t	start_time;

	start_time = get_ms();
	while (get_ms() - start_time < time_to_sleep_ms)
	{
		if (can_die && is_dead_routine(p))
			return ;
		usleep(500);
	}
	return ;
}

void	eat(t_philo *p, bool is_even)
{
	pthread_mutex_lock(p->fork[!is_even]);
	locked_print("has taken a fork", p);
	pthread_mutex_lock(p->fork[is_even]);
	locked_print("has taken a fork", p);
	pthread_mutex_lock(p->is_eating_lock);
	p->is_eating = 1;
	pthread_mutex_unlock(p->is_eating_lock);
	locked_print("is " GREEN "eating" RESET, p);
	pthread_mutex_lock(p->meal_lock);
	p->time_of_last_meal = get_ms();
	pthread_mutex_unlock(p->meal_lock);
	sleep_if_not_dead(p, p->infos.time_to_eat, 1);
	pthread_mutex_unlock(p->fork[!is_even]);
	pthread_mutex_unlock(p->fork[is_even]);
	pthread_mutex_lock(p->is_eating_lock);
	p->is_eating = 0;
	pthread_mutex_unlock(p->is_eating_lock);
	pthread_mutex_lock(p->meal_lock);
	if (p->infos.must_eat)
		p->meals_eaten++;
	pthread_mutex_unlock(p->meal_lock);
	return ;
}

void	think(t_philo *p)
{
	locked_print("is " YELLOW "thinking" RESET, p);
	if (p->infos.time_to_eat > p->infos.time_to_sleep)
		sleep_if_not_dead(p, p->infos.time_to_eat * 2 - p->infos.time_to_sleep,
			1);
	return ;
}

void	slip(t_philo *p)
{
	locked_print("is " BLUE "sleeping" RESET, p);
	return (sleep_if_not_dead(p, p->infos.time_to_sleep, 1));
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)(philosopher);
	pthread_mutex_lock(philo->meal_lock);
	philo->start_time = get_ms();
	philo->time_of_last_meal = get_ms();
	pthread_mutex_unlock(philo->meal_lock);
	while (!is_dead_routine(philo))
	{
		if (!is_dead_routine(philo))
			eat(philo, !(philo->id % 2));
		if (!is_dead_routine(philo))
			slip(philo);
		if (!is_dead_routine(philo))
			think(philo);
	}
	return (NULL);
}
