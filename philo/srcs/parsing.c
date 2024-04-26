/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/23 11:36:06 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_values(bool *minus, bool *nb_set, size_t *i, long int *nb)
{
	*minus = 0;
	*nb_set = 0;
	*i = 0;
	*nb = 0;
}

static long int	ends_with_whitespaces(const char *s, long int nb, size_t i)
{
	while (s[++i])
		if (!is_whitespace(s[i]))
			return (-1);
	return (nb);
}

static void	skip_prefix(const char *s, size_t *i, bool *minus)
{
	while (is_whitespace(s[*i]))
		(*i)++;
	if (s[*i] == '+')
		(*i)++;
	if (s[*i] == '-')
	{
		*minus = 1;
		(*i)++;
	}
}

static long int	zero_or_err(const char *s, size_t i, bool *nb_set, long int *nb)
{
	while (s[i])
	{
		if (*nb_set && is_whitespace(s[i]))
			return (ends_with_whitespaces(s, *nb, i));
		if (s[i] != '0')
			return (-1);
		(*nb) = (*nb) * 10 + s[i] - '0';
		if ((*nb) > INT_MAX)
			return (-1);
		if (!(*nb_set))
			(*nb_set) = 1;
		i++;
	}
	return (*nb);
}

long int	atoi_is_unsignedint(const char *s)
{
	long int	nb;
	bool		nb_set;
	bool		minus_zero;
	size_t		i;

	init_values(&minus_zero, &nb_set, &i, &nb);
	skip_prefix(s, &i, &minus_zero);
	if (!s[i])
		return (-1);
	if (minus_zero)
		return (zero_or_err(s, i, &nb_set, &nb));
	while (s[i])
	{
		if (nb_set && is_whitespace(s[i]))
			return (ends_with_whitespaces(s, nb, i));
		if (!is_nb(s[i]))
			return (-1);
		nb = nb * 10 + s[i] - '0';
		if (nb > INT_MAX)
			return (-1);
		if (!nb_set)
			nb_set = 1;
		i++;
	}
	return (nb);
}
