/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/27 01:13:41 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	main(int argc, char *argv[])
{
	t_arguments arguments;
	t_philo *philosophers;
	pthread_mutex_t *forks;
	pthread_t *threads;
	struct timeval t;
	int start_time;
	int i;
	int death_tracker;

	i = 0;
	if (!validate_input(argc, argv))
	{
		write(1, "Arguments not valid!", 21);
		return (1);
	}
	parse_arguments(argv, &arguments);
	pthread_mutex_init(&arguments.print_mutex,NULL);
	forks = init_mutex(&arguments);
	if(forks == NULL)
		return(1);
	gettimeofday(&t,NULL);
	start_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	arguments.start_time = start_time;
	threads = init_threads(&arguments,&philosophers,forks);
	if(threads == NULL)
		return(1);
	while(1)
	{
		i = 0;
		int finished_count = 0;
		while(i < arguments.number_of_philosphers)
		{
			gettimeofday(&t,NULL);
			int current_time = (t.tv_sec * 1000) + (t.tv_usec / 1000) - start_time;
			pthread_mutex_lock(&philosophers[i].meal_mutex);
			death_tracker = philosophers[i].last_meal_time;
			if(arguments.number_of_times_each_philosopher_must_eat != -1
				&& philosophers[i].meals_eaten >= arguments.number_of_times_each_philosopher_must_eat)
				finished_count++;
			pthread_mutex_unlock(&philosophers[i].meal_mutex);
			if((current_time - death_tracker) > arguments.time_to_die)
			{
				pthread_mutex_lock(&arguments.print_mutex);
				printf("%d %d died\n", current_time, philosophers[i].philosopher_id);
				free(threads);
				free(forks);
				free(philosophers);
				return (0);
			}
			i++;
		}
		if(finished_count == arguments.number_of_philosphers)
		{
			pthread_mutex_lock(&arguments.print_mutex);
			free(threads);
			free(forks);
			free(philosophers);
			return (0);
		}
	}
	return (0);
}
