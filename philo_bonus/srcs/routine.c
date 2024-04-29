/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:51:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 05:26:24 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_if_not_dead(t_philo *p, size_t time_to_sleep_ms)
{
	size_t	start_time;

	start_time = get_ms();
	while (get_ms() - start_time < time_to_sleep_ms)
	{
		if (is_dead(p))
			(exit_simulation(p));
		usleep(500);
	}
	return ;
}

void	eat(t_philo *p)
{
	if (sem_wait(p->sem.forks) == -1)
		exit_and_print(p, "sem_wait failed");
	print("has taken a fork", p);
	if (sem_wait(p->sem.forks) == -1)
		exit_and_print(p, "sem_wait failed");
	print("has taken a fork", p);
	sem_wait(p->sem.is_eating_lock);
	p->is_eating = 1;
	sem_post(p->sem.is_eating_lock);
	sem_wait(p->sem.meal_lock);
	p->time_of_last_meal = get_ms();
	sem_post(p->sem.meal_lock);
	print("is " GREEN "eating" RESET, p);
	sleep_if_not_dead(p, p->infos.time_to_eat);
	if (sem_post(p->sem.forks) == -1)
		exit_and_print(p, "sem_post failed");
	if (sem_post(p->sem.forks) == -1)
		exit_and_print(p, "sem_post failed");
	sem_wait(p->sem.is_eating_lock);
	p->is_eating = 0;
	sem_post(p->sem.is_eating_lock);
	if (p->infos.must_eat)
	{
		sem_wait(p->sem.meal_lock);
		p->meals_eaten++;
		sem_post(p->sem.meal_lock);
		if (p->meals_eaten == p->infos.nb_times_must_eat)
			exit_simulation(p);
	}
	return ;
}

void	think(t_philo *p)
{
	print("is " YELLOW "thinking" RESET, p);
	if (p->infos.time_to_eat > p->infos.time_to_sleep)
		sleep_if_not_dead(p, p->infos.time_to_eat * 2 - p->infos.time_to_sleep);
	return ;
}

void	slip(t_philo *p)
{
	print("is " BLUE "sleeping" RESET, p);
	return (sleep_if_not_dead(p, p->infos.time_to_sleep));
}

void	routine(t_philo *philo)
{
	sem_wait(philo->sem.meal_lock);
	philo->time_of_last_meal = get_ms();
	philo->start_time = get_ms();
	sem_post(philo->sem.meal_lock);
	if (pthread_create(&philo->monitor, NULL, monitor, philo) == -1)
		exit_simulation(philo);
	if (pthread_detach(philo->monitor) != 0)
		exit_simulation(philo);
	while (!is_dead(philo))
	{
		if (!is_dead(philo))
			eat(philo);
		if (!is_dead(philo))
			slip(philo);
		if (!is_dead(philo))
			think(philo);
	}
	exit_simulation(philo);
}
