/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:58:17 by cviegas           #+#    #+#             */
/*   Updated: 2024/03/29 12:22:26 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	size_t	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	philo_must_eat;
}			t_philo;

/* Colors */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"
# define BOLD "\033[1m"

# define ERR_0 "The program takes 4 or 5 arguments:\n"
# define ERR_1 "    • number_of_philosophers\n    • time_to_die\n    "
# define ERR_2 "• time_to_eat\n    • time_to_sleep\n    "
# define ERR_3 "• (optional) number_of_times_each_philosopher_must_eat\n"
# define ERR_NB "Entries needs to be only unsigned int values\n"
# define FAIL EXIT_FAILURE

/* FUNCTIONS */
long int	atoi_is_unsignedint(const char *s);
bool		is_nb(char c);
size_t		len(const char *s);
bool		is_whitespace(char c);

#endif