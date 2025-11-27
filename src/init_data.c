/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:21:59 by msafa             #+#    #+#             */
/*   Updated: 2025/11/26 16:39:13 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

pthread_mutex_t *init_mutex(t_arguments *arguments)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * arguments->number_of_forks);
    if(!forks)
        return(NULL);
    while(i < arguments->number_of_forks)
	{
        pthread_mutex_init(&forks[i++],NULL);
	}
	return(forks);
}

pthread_t *init_threads(t_arguments *arguments,t_philo **philosophers,pthread_mutex_t *forks )
{
	pthread_t *threads;
	int i;
	
	i = 0;
	*philosophers = malloc(sizeof(t_philo) * arguments->number_of_philosphers);
	if(!*philosophers)
		return(NULL);
	threads = malloc(sizeof(pthread_t) * arguments->number_of_philosphers);
	if(!threads)
		return(free(*philosophers),NULL);
	while(i < (*arguments).number_of_philosphers)
	{
		(*philosophers)[i].philosopher_id = i + 1;
		(*philosophers)[i].left_fork = &forks[i];
		(*philosophers)[i].right_fork = &forks[(i + 1) % arguments->number_of_philosphers];
		(*philosophers)[i].last_meal_time = 0;
		(*philosophers)[i].eating_start_time = 0;
		(*philosophers)[i].eating_finish_time = 0;
		pthread_mutex_init(&(*philosophers)[i].meal_mutex, NULL);
		(*philosophers)[i].arguments = arguments;
		if(pthread_create(&threads[i],NULL,dining,&(*philosophers)[i]) != 0)
		{
			perror("Failed to create thread");
			return(NULL);
		}
		pthread_detach(threads[i]);
		i++;
	}
	return(threads);
}
