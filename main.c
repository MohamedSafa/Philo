/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/24 01:06:02 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int only_digits(char *s)
{
	int i;
	
	i = 0;
	while(s[i])
	{
		if(!(s[i] >= '0' && s[i] <= '9'))
			return(0);
		i++;
	}
	return(1);
}

int	validate_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6 )
		return(0);
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (0);
		if(!only_digits(argv[i]))
			return (0);
		if (atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

void	parse_arguments(char *argv[], t_arguments *arguments)
{
	arguments->number_of_philosphers = atoi(argv[1]);
	arguments->number_of_forks = atoi(argv[1]);
	arguments->time_to_die = atoi(argv[2]);
	arguments->time_to_eat = atoi(argv[3]);
	arguments->time_to_sleep = atoi(argv[4]);
	if(argv[5])
		arguments->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	
}

pthread_mutex_t *init_mutex(t_arguments *arguments)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * arguments->number_of_forks);
    if(!forks)
        return(NULL);
    while(i < arguments->number_of_forks)
        pthread_mutex_init(&forks[i++],NULL);
	return(forks);
}

pthread_t *init_threads(t_arguments arguments,t_philo *philosophers)
{
	pthread_t *threads;
	int i;
	
	i = 0;
	philosophers = malloc(sizeof(t_philo) * philosophers->arguments->number_of_philosphers);
	if(!philosophers)
		return(NULL);
	threads = malloc(sizeof(pthread_t) * philosophers->arguments->number_of_philosphers);
	if(!threads)
		return(NULL);
	while(i < philosophers->arguments->number_of_philosphers)
	{
		philosophers[i].philosopher_id = i + 1;
		if(pthread__create(&threads[i],NULL,dining,&philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			return(NULL);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_arguments arguments;
	t_philo *philosophers;
	pthread_mutex_t *forks;
	pthread_t *threads;

	if (!validate_input(argc, argv))
	{
		write(1, "Arguments not valid!", 21);
		return (1);
	}
	parse_arguments(argv, &arguments);
	forks = init_mutex(&arguments);
	threads = init_threads(arguments,philosophers);
	
	return (0);
}