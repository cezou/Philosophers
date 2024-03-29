/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 11:39:34 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/29 12:01:42 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	atoi_is_unsignedint(const char *s)
{
	long int	nb;
	size_t		i;

	i = 0;
	nb = 0;
	while (is_whitespace(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	if (!s[i])
		return (-1);
	while (s[i])
	{
		if (!is_nb(s[i]))
			return (-1);
		nb = nb * 10 + s[i] - '0';
		if (nb > UINT_MAX)
			return (-1);
		i++;
	}
	return (nb);
}
