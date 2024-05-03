/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:51:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 10:35:44 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_if_not_dead(t_philo *p, size_t time_to_sleep_ms)
{
	size_t	start_time;

	start_time = get_ms();
	while (get_ms() - start_time < time_to_sleep_ms)
	{
		routine_check_dead(p);
		usleep(500);
	}
	return ;
}

void	eat(t_philo *p)
{
	routine_check_dead(p);
	sem_wait(p->sem.forks);
	print("has taken a fork", p);
	routine_check_dead(p);
	sem_wait(p->sem.forks);
	print("has taken a fork", p);
	routine_check_dead(p);
	p->is_eating = 1;
	p->time_of_last_meal = get_ms();
	print("is " GREEN "eating" RESET, p);
	sleep_if_not_dead(p, p->infos.time_to_eat);
	sem_post(p->sem.forks);
	sem_post(p->sem.forks);
	p->is_eating = 0;
	if (p->infos.must_eat)
	{
		p->meals_eaten++;
		if (p->meals_eaten == p->infos.nb_times_must_eat)
			sem_post(p->sem.everyone_ate);
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

void	routine(t_philo philo)
{
	sem_wait(philo.sem.there_is_a_dead);
	sem_wait(philo.sem.everyone_ate);
	wait_everyone_to_start(philo);
	philo.time_of_last_meal = get_ms();
	philo.start_time = get_ms();
	if (philo.id % 2)
		sleep_if_not_dead(&philo, philo.infos.time_to_eat);
	while (1)
	{
		routine_check_dead(&philo);
		eat(&philo);
		routine_check_dead(&philo);
		slip(&philo);
		routine_check_dead(&philo);
		think(&philo);
	}
	close_sem(&philo.sem);
}
