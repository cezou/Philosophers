/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:56:06 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/29 12:33:22 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_value_or_exit(long int entry, size_t *nb)
{
	if (entry == -1)
	{
		printf(RED BOLD "ERROR: " RESET RED ERR_NB RESET);
		exit(FAIL);
	}
	*nb = entry;
}

void	init_philo(t_philo *p, int ac, char **av)
{
	set_value_or_exit(atoi_is_unsignedint(av[1]), &p->nb_philo);
	set_value_or_exit(atoi_is_unsignedint(av[2]), &p->time_to_die);
	set_value_or_exit(atoi_is_unsignedint(av[3]), &p->time_to_eat);
	set_value_or_exit(atoi_is_unsignedint(av[4]), &p->time_to_sleep);
	if (ac == 6)
		set_value_or_exit(atoi_is_unsignedint(av[5]), &p->philo_must_eat);
}

int	main(int ac, char **av)
{
	t_philo	p;

	if (ac < 5 || ac > 6)
		return (printf(RED BOLD ERR_0 RESET RED ERR_1 ERR_2 ERR_3 RESET), FAIL);
	init_philo(&p, ac, av);
}
