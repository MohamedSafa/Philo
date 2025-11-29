/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:21:59 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:05:45 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_current_time(void)
{
	struct timeval	t;
	int				current_time;

	gettimeofday(&t, NULL);
	current_time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (current_time);
}

pthread_mutex_t	*init_mutex(t_arguments *arguments)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * arguments->number_of_forks);
	if (!forks)
		return (NULL);
	while (i < arguments->number_of_forks)
	{
		pthread_mutex_init(&forks[i++], NULL);
	}
	return (forks);
}

static void	fill_philosopher(t_philo *philo, int i, t_arguments *args,
		pthread_mutex_t *forks)
{
	philo->philosopher_id = i + 1;
	philo->left_fork = &forks[i];
	philo->right_fork = &forks[(i + 1) % args->number_of_philosphers];
	philo->last_meal_time = 0;
	philo->eating_start_time = 0;
	philo->meals_eaten = 0;
	pthread_mutex_init(&philo->meal_mutex, NULL);
	philo->arguments = args;
}

pthread_t	*init_threads(t_arguments *arguments, t_philo **philosophers,
		pthread_mutex_t *forks)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	*philosophers = malloc(sizeof(t_philo) * arguments->number_of_philosphers);
	if (!*philosophers)
		return (NULL);
	threads = malloc(sizeof(pthread_t) * arguments->number_of_philosphers);
	if (!threads)
	{
		free(*philosophers);
		return (NULL);
	}
	while (i < arguments->number_of_philosphers)
	{
		fill_philosopher(&(*philosophers)[i], i, arguments, forks);
		if (pthread_create(&threads[i], NULL, dining, &(*philosophers)[i]) != 0)
		{
			write(2, "Failed to create thread\n", 24);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

int	init_data(t_arguments *arguments, t_philo **philosophers)
{
	pthread_mutex_init(&arguments->print_mutex, NULL);
	pthread_mutex_init(&arguments->death_mutex, NULL);
	arguments->simulation_running = 1;
	arguments->forks = init_mutex(arguments);
	if (arguments->forks == NULL)
		return (0);
	arguments->start_time = get_current_time();
	arguments->threads = init_threads(arguments, philosophers,
			arguments->forks);
	if (arguments->threads == NULL)
		return (0);
	return (1);
}
