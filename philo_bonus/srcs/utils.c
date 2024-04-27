/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 06:50:26 by cviegas          ###   ########.fr       */
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

void	print(char *s, t_philo *p)
{
	if (!is_dead(p))
		printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
}

void	print_dead(char *s, t_philo *p)
{
	printf("%zu %zu %s\n", get_philo_age(p), p->id, s);
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
