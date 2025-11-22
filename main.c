/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/10 14:59:58 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo.h"

int	validate_input(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		while (i < argc)
		{
			if (!argv[i] || !argv[i][0])
				return (0);
			i++;
		}
	}
	return (1);
}

void	parse_argumets(char *argv[], t_arguments *arguments)
{
	arguments->number_of_philosphers = argv[1];
	arguments->number_of_forks = argv[1];
	arguments->time_to_die = argv[2];
	arguments->time_to_eat = argv[3];
	arguments->time_to_sleep = argv[4];
	arguments->number_of_times_each_philosopher_must_eat = argv[5];
}

pthread_mutex_t	*init_mutex(t_arguments *arguments)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * arguments->number_of_forks);
    if(!forks)
        return(NULL);
    while(i < arguments->number_of_forks)
        pthread_mutex_init(&forks[i++],NULL);
}

int	main(int argc, char *argv[])
{
	t_arguments arguments;
	t_philo philosophers;
	pthread_mutex_t *forks;

	if (!validate_input(argc, argv))
		write(1, "Arguments not valid!", 21);
	parse_arguments(argv, &arguments);
	forks = init_mutex(&arguments);
	

	return (0);
}