/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/25 20:32:06 by msafa            ###   ########.fr       */
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
	forks = init_mutex(&arguments);
	if(forks == NULL)
		return(1);
	gettimeofday(&t,NULL);
	start_time = t.tv_sec;
	arguments.start_time = start_time;
	threads = init_threads(&arguments,&philosophers,forks);
	if(threads == NULL)
		return(1);
	while(1)
	{
		i = 0;
		while(i < arguments.number_of_philosphers)
		{
			gettimeofday(&t,NULL);
			death_tracker = ((t.tv_sec - arguments.start_time) * 1000) - philosophers[i].last_meal_time;
			if(death_tracker > arguments.time_to_die)
				break;
			i++;
		}
		if(i < arguments.number_of_philosphers)
			break;
	}
	void *ret;
	int j =0;
	while(j < arguments.number_of_philosphers)
	{
		pthread_join(threads[j],&ret);
		j++;
	}
	return (0);
}
