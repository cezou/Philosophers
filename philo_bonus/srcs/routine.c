/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:51:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 06:51:29 by cviegas          ###   ########.fr       */
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
			(print_dead(RED "died" RESET, p), sem_close(p->forks),
				sem_unlink("/sem_" SEM_NAME), exit(p->id));
		usleep(500);
	}
	return ;
}

void	exit_and_print(t_philo *p, char *message)
{
	sem_close(p->forks);
	sem_unlink("/sem_" SEM_NAME);
	err(message);
	exit(p->id);
}

void	eat(t_philo *p)
{
	if (sem_wait(p->forks) == -1)
		exit_and_print(p, "sem_wait failed");
	print("has taken a fork", p);
	if (sem_wait(p->forks) == -1)
		exit_and_print(p, "sem_wait failed");
	print("has taken a fork", p);
	p->is_eating = 1;
	print("is " GREEN "eating" RESET, p);
	p->time_of_last_meal = get_ms();
	sleep_if_not_dead(p, p->infos.time_to_eat);
	if (sem_post(p->forks) == -1)
		exit_and_print(p, "sem_post failed");
	if (sem_post(p->forks) == -1)
		exit_and_print(p, "sem_post failed");
	p->is_eating = 0;
	if (p->infos.must_eat)
	{
		p->meals_eaten++;
		if (p->meals_eaten == p->infos.nb_times_must_eat)
			(sem_close(p->forks), sem_unlink(SEM_NAME), exit(p->id));
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
	philo->start_time = get_ms();
	philo->time_of_last_meal = get_ms();
	while (!is_dead(philo))
	{
		if (!is_dead(philo))
			eat(philo);
		if (!is_dead(philo))
			slip(philo);
		if (!is_dead(philo))
			think(philo);
	}
	(print_dead(RED "died" RESET, philo), exit(philo->id));
}
