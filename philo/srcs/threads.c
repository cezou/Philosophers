/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:05:51 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/03 11:17:46 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*alone(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	p->start_time = get_ms();
	p->time_of_last_meal = get_ms();
	printf("%zu %zu %s\n", get_ms() - p->start_time, p->id, "has taken a fork");
	usleep(p->infos.time_to_die * 1000);
	printf("%zu %zu %s\n", get_ms() - p->start_time, p->id, RED "died" RESET);
	return (NULL);
}

bool	create_alone(t_infos infos)
{
	t_philo	p;

	p.infos = infos;
	p.id = 1;
	if (pthread_create(&p.thread, NULL, alone, &p) != 0)
		return (err(T_ERR_1), FAIL);
	if (pthread_join(p.thread, NULL) != 0)
		return (err(T_ERR_2), FAIL);
	return (SUCCESS);
}

int	create_threads(t_vars *v, t_infos infos)
{
	size_t	i;

	i = 0;
	while (i < infos.nb_philo)
	{
		if (pthread_create(&v->philos[i].thread, NULL, routine,
				&v->philos[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_create(&v->monitor, NULL, monitor, &v->philos) != 0)
		return (-1);
	return (0);
}

int	join_threads(t_vars *v, t_infos infos)
{
	size_t	i;

	i = 0;
	while (i < infos.nb_philo)
	{
		if (pthread_join(v->philos[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_join(v->monitor, NULL) != 0)
		return (-1);
	return (0);
}
