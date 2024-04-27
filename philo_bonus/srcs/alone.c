/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:58:16 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 18:18:54 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// (cheh t'es tout seul)
void	eat_alone(t_philo *p)
{
	pthread_mutex_lock(p->fork[0]);
	locked_print("has taken a fork", p);
	pthread_mutex_lock(p->is_eating_lock);
	p->is_eating = 1;
	pthread_mutex_unlock(p->is_eating_lock);
	locked_print("is " GREEN "eating" RESET, p);
	pthread_mutex_lock(p->meal_lock);
	p->time_of_last_meal = get_ms();
	pthread_mutex_unlock(p->meal_lock);
	sleep_if_not_dead(p, p->infos.time_to_eat, 1);
	pthread_mutex_unlock(p->fork[0]);
	pthread_mutex_lock(p->is_eating_lock);
	p->is_eating = 0;
	pthread_mutex_unlock(p->is_eating_lock);
	if (p->infos.must_eat)
		p->meals_eaten++;
	return ;
}
