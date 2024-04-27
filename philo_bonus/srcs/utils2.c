/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 07:04:56 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 07:07:04 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err(char *s)
{
	printf(RED BOLD "ERROR: " RESET RED "%s%s\n", s, RESET);
}

void	print(char *s, t_philo *p)
{
	if (!is_dead(p))
		printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
}

void	print_dead(char *s, t_philo *p)
{
	printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
}
