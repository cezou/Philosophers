/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:58:17 by cviegas           #+#    #+#             */
/*   Updated: 2024/04/27 07:17:32 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAX_PHILOS 200
# define LEFT 0
# define RIGHT 1

typedef struct s_infos
{
	size_t	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	bool	must_eat;
	size_t	nb_times_must_eat;
	size_t	start_time;
}			t_infos;

typedef struct s_philo
{
	pid_t	process;

	t_infos	infos;
	sem_t	*forks;
	size_t	start_time;
	size_t	id;
	bool	is_eating;
	size_t	meals_eaten;
	size_t	time_of_last_meal;
	bool	*is_dead;

}			t_philo;

// typedef enum e_action
// {
// 	EVERYONE_HAS_EATEN,
// 	THERE_IS_A_DEAD,
// 	SEM_POST_FAILED,
// 	SEM_WAIT_FAILED,
// };

/* Colors */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define SEM_NAME "aaaaaaaaaaa"

# define ERR_0 "The program takes 4 or 5 arguments:\n"
# define ERR_1 "    • number_of_philosophers\n    • time_to_die\n    "
# define ERR_2 "• time_to_eat\n    • time_to_sleep\n    "
# define ERR_3 "• (optional) number_of_times_each_philosopher_must_eat\n"
# define ERR_NB "Entries needs to be only unsigned int values\n"
# define T_ERR_0 "Problem during a mutex initiation"
# define T_ERR_1 "Problem during a thread creation"
# define T_ERR_2 "Problem during a thread joining"
# define FAIL EXIT_FAILURE

/* FUNCTIONS */
void		exit_and_print(t_philo *p, char *message);
void		print_dead(char *s, t_philo *p);

/*		Init		*/
long int	atoi_is_unsignedint(const char *s);
void		set_infos(t_infos *infos, char **av);
int			init_philos(t_philo *philos, t_infos infos, sem_t *forks);

/*		Routine		*/
void		routine(t_philo *philo);
void		eat(t_philo *p);
void		slip(t_philo *p);
bool		is_dead(t_philo *philo);

/*		Utils		*/
bool		is_nb(char c);
bool		is_whitespace(char c);
void		err(char *s);
size_t		get_ms(void);
void		think(t_philo *p);
size_t		get_last_meal(t_philo *p);
bool		is_eating(t_philo *philo);
size_t		get_philo_age(t_philo *p);
void		print(char *s, t_philo *p);

#endif