/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 07:04:56 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/02 22:33:55 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err(char *s)
{
	printf(RED BOLD "ERROR: " RESET RED "%s%s\n", s, RESET);
}

void	print(char *s, t_philo *p)
{
	printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
}

void	routine_check_dead(t_philo *p)
{
	if (!p->is_eating && get_ms() - p->time_of_last_meal > p->infos.time_to_die)
	{
		sem_wait(p->sem.someone_died);
		print(RED "died" RESET, p);
		sem_post(p->sem.there_is_a_dead);
		close_sem(&p->sem);
		exit(1);
	}
}

size_t	get_philo_age(t_philo *p)
{
	return (get_ms() - p->start_time);
}
