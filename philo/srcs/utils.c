/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/25 11:10:44 by cviegas          ###   ########.fr       */
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

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// size_t	get_philo_age(t_philo p)
// {
// 	return (p.start_time - get_ms());
// }

void	locked_print(char *s, t_philo *p)
{
	pthread_mutex_lock(p->write_lock);
	if (!(*p->is_dead))
		printf("%zu %zu %s\n", get_ms() - p->start_time, p->id, s);
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
