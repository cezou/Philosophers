/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:36:17 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/29 04:05:28 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_null_sem(t_semaphores *sem)
{
	sem->forks = NULL;
	sem->is_dead_lock = NULL;
	sem->meal_lock = NULL;
	sem->is_there_a_dead = NULL;
	sem->is_there_a_dead_lock = NULL;
	sem->is_eating_lock = NULL;
}

t_semaphores	init_sem(t_infos infos)
{
	t_semaphores	sem;

	set_null_sem(&sem);
	sem_unlink("/sem_" SEM_NAME);
	sem_unlink("/sem_dead_" SEM_NAME);
	sem_unlink("/sem_is_dead_lock_" SEM_NAME);
	sem_unlink("/sem_meal_lock_" SEM_NAME);
	sem_unlink("/sem_is_there_a_dead_" SEM_NAME);
	sem_unlink("/sem_is_there_a_dead_lock_" SEM_NAME);
	sem_unlink("/sem_is_eating_lock_" SEM_NAME);
	sem.forks = sem_open("/sem_" SEM_NAME, O_CREAT, 777, infos.nb_philo);
	sem.is_dead_lock = sem_open("/sem_is_dead_lock_" SEM_NAME, O_CREAT, 777, 1);
	sem.meal_lock = sem_open("/sem_meal_lock_" SEM_NAME, O_CREAT, 777, 1);
	sem.is_there_a_dead = sem_open("/sem_is_there_a_dead_" SEM_NAME, O_CREAT,
			777, 1);
	sem.is_there_a_dead_lock = sem_open("/sem_is_there_a_dead_lock_" SEM_NAME,
			O_CREAT, 777, 1);
	sem.is_eating_lock = sem_open("/sem_is_eating_lock_" SEM_NAME, O_CREAT, 777,
			1);
	if (!sem.forks || !sem.is_dead_lock || !sem.meal_lock
		|| !sem.is_there_a_dead || !sem.is_there_a_dead_lock
		|| !sem.is_eating_lock)
		(err("sem_open failed"), close_sem(&sem), exit(FAIL));
	sem_wait(sem.is_there_a_dead);
	return (sem);
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
	p_semclose(sem->is_dead_lock, "/sem_is_dead_lock_" SEM_NAME);
	p_semclose(sem->meal_lock, "/sem_meal_lock_" SEM_NAME);
	p_semclose(sem->is_there_a_dead, "/sem_is_there_a_dead_" SEM_NAME);
	p_semclose(sem->is_there_a_dead_lock,
		"/sem_is_there_a_dead_lock_" SEM_NAME);
	p_semclose(sem->is_eating_lock, "/sem_is_eating_lock_" SEM_NAME);
}
