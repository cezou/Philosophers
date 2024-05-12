/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/12 04:28:35 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_nb(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

size_t	get_ms(void)
{
	struct timeval	time;
	long int		ms;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (ms <= 0)
		return (0);
	return (ms);
}

void	wait_everyone_to_start(t_philo philo)
{
	if ((int)(philo.start_time + 500) - get_ms())
		usleep(1000 * (philo.start_time + 500 - get_ms()));
}

void	routine_check_dead(t_philo *p)
{
	if (!p->is_eating && get_ms()
		- p->time_of_last_meal >= p->infos.time_to_die)
	{
		sem_wait(p->sem.someone_died);
		print_dead(p);
		sem_post(p->sem.there_is_a_dead);
		close_sem(&p->sem);
		exit(1);
	}
}
