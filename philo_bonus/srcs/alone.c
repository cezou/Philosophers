/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 22:22:46 by cviegas           #+#    #+#             */
/*   Updated: 2024/05/02 22:56:49 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	alone(t_philo *p)
{
	p->start_time = get_ms();
	p->time_of_last_meal = get_ms();
	print("has taken a fork", p);
	sleep_if_not_dead(p, p->infos.time_to_die);
	print(RED "died" RESET, p);
}
