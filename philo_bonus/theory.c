/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:55:45 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 04:05:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*mutex;
sem_t	*is_there_a_dead_philo;

void	init(void)
{
}

int	main(int ac, char **av)
{
	mutex = sem_open("/sem_dead_" SEM_NAME, O_CREAT, 777, 1);
	is_there_a_dead_philo = sem_open("/sem_dead_" SEM_NAME, O_CREAT, 777, 1);
	sem_wait(is_there_a_dead_philo); // passe a zero
										// thread: monitor pour chaque philo
}

void	*monitor(t_philo *philo)
{
	while (1)
	{
		sem_wait(mutex);
		if (sem_post(is_there_a_dead_philo) == EOVERFLOW)
		{
			philo->is_dead = 0;
			sem_post(mutex);
			return (0);
		}
		sem_wait(is_there_a_dead_philo);
		sem_post(mutex);

		if (philo->time_of_last_meal - get_ms() > philo->infos.start_time)
		{
			philo->is_dead = 0;
			sem_post(is_there_a_dead_philo);
			return (0);
		}
	}
	sem_post(mutex);
}