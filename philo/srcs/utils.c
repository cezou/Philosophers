/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/26 17:57:24 by cviegas          ###   ########.fr       */
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

void	locked_print(char *s, t_philo *p)
{
	pthread_mutex_lock(p->write_lock);
	if (!is_dead_routine(p))
		printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
	pthread_mutex_unlock(p->write_lock);
}

void	err(char *s)
{
	printf(RED BOLD "ERROR: " RESET RED "%s%s\n", s, RESET);
}

// ft_strlen For more code visibility
// size_t	len(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i++])
// 		;
// 	return (i);
// }
