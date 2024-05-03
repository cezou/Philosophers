/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 07:04:56 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 10:33:05 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err(char *s)
{
	printf(RED "ERROR: " RESET RRED "%s%s\n", s, RESET);
}

void	print(char *s, t_philo *p)
{
	sem_wait(p->sem.someone_died);
	printf("%zu %zu %s\n", get_ms() - p->start_time, p->id, s);
	sem_post(p->sem.someone_died);
}

void	print_dead(t_philo *p)
{
	printf("%zu %zu" RED " died" RESET "\n", get_ms() - p->start_time, p->id);
}

void	p_semclose(sem_t *sem, char *name)
{
	if (sem)
	{
		sem_close(sem);
		sem_unlink(name);
	}
}

void	close_sem(t_semaphores *sem)
{
	p_semclose(sem->forks, "/sem_" SEM_NAME);
	p_semclose(sem->everyone_ate, "/sem_everyone_ate_" SEM_NAME);
	p_semclose(sem->there_is_a_dead, "/sem_there_is_a_dead_" SEM_NAME);
	p_semclose(sem->someone_died, "/sem_someone_died_" SEM_NAME);
	p_semclose(sem->start, "/sem_start_" SEM_NAME);
}
