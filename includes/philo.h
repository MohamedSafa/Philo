/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:33:03 by msafa             #+#    #+#             */
/*   Updated: 2025/11/25 01:24:47 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef struct s_arguments   
{
    int number_of_philosphers;
    int number_of_forks;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
} t_arguments;

typedef struct s_philo
{
    int philosopher_id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int last_meal_time;
    t_arguments *arguments;
}t_philo;

// Parsing functions
int		only_digits(char *s);
int		validate_input(int argc, char *argv[]);
void	parse_arguments(char *argv[], t_arguments *arguments);

// Initialization functions
pthread_mutex_t	*init_mutex(t_arguments *arguments);
pthread_t		*init_threads(t_arguments *arguments, t_philo **philosophers, pthread_mutex_t *forks);

// Dining function
void	*dining(void *arg);

#endif