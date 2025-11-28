/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:33:03 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:08:50 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_arguments
{
	int				number_of_philosphers;
	int				number_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				start_time;
	int				simulation_running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}					t_arguments;

typedef struct s_philo
{
	int				philosopher_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				last_meal_time;
	int				eating_start_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	t_arguments		*arguments;
}					t_philo;

// Parsing functions
int					only_digits(char *s);
int					validate_input(int argc, char *argv[]);
void				parse_arguments(char *argv[], t_arguments *arguments);

// Initialization functions
pthread_mutex_t		*init_mutex(t_arguments *arguments);
pthread_t			*init_threads(t_arguments *arguments,
						t_philo **philosophers, pthread_mutex_t *forks);
int					init_data(t_arguments *arguments, t_philo **philosophers);

// Dining functions
void				*dining(void *arg);
void				start_dining(t_arguments *arguments, t_philo *philosophers);

// Dining utility functions
void				print_status(t_philo *philo, char *msg, int timestamp);
int					check_simulation_status(t_philo *philo);
int					get_timestamp(t_philo *philo);
int					get_current_time(void);
void				take_left_fork(t_philo *philo);
void				take_right_fork(t_philo *philo);
void				start_eating(t_philo *philo);

#endif