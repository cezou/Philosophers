/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:36:17 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/02 22:12:35 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
