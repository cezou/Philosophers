/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 02:51:02 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 10:23:07 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_everyone(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos[0].infos.nb_philo)
	{
		if (philos[i].process == -1)
			break ;
		kill(philos[i].process, SIGKILL);
		i++;
	}
}

void	*check_meals(void *philosophers)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philosophers;
	i = -1;
	if ((int)((*philos).start_time + 500) - get_ms())
		usleep(1000 * ((*philos).start_time + 500 - get_ms()));
	while (++i < (int)(*philos).infos.nb_philo)
		sem_wait((*philos).sem.everyone_ate);
	sem_post((*philos).sem.there_is_a_dead);
	return (NULL);
}

void	*check_dead(void *philosophers)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)philosophers;
	i = -1;
	if ((int)((*philos).start_time + 500) - get_ms())
		usleep(1000 * ((*philos).start_time + 500 - get_ms()));
	sem_wait((*philos).sem.there_is_a_dead);
	while (++i < (int)(*philos).infos.nb_philo)
		sem_post((*philos).sem.everyone_ate);
	kill_everyone(philos);
	return (NULL);
}

void	create_monitor(t_philo *philos)
{
	pthread_t	dead;
	pthread_t	meals;

	if (philos[0].infos.must_eat && pthread_create(&meals, NULL, check_meals,
			philos) != 0)
		(err(T_ERR_1), close_sem(&philos->sem), exit(FAIL));
	if (pthread_create(&dead, NULL, check_dead, philos) != 0)
		(err(T_ERR_1), close_sem(&philos->sem), exit(FAIL));
	if (pthread_detach(dead) != 0)
		(err(T_ERR_2), close_sem(&philos->sem), exit(FAIL));
	if (philos[0].infos.must_eat && pthread_detach(meals) != 0)
		(err(T_ERR_2), close_sem(&philos->sem), exit(FAIL));
}

int	wait_for_childs(size_t nb_philo, t_semaphores sem)
{
	int	status;
	int	i;

	i = 0;
	while (++i < (int)nb_philo)
		waitpid(-1, &status, 0);
	close_sem(&sem);
	return (0);
}
