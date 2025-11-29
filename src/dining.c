/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:28:31 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 21:24:47 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_simulation_status(t_philo *philo)
{
	int	running;

	pthread_mutex_lock(&philo->arguments->death_mutex);
	running = philo->arguments->simulation_running;
	pthread_mutex_unlock(&philo->arguments->death_mutex);
	return (running);
}

static void	odd_philosopher_routine(t_philo *philo)
{
	int	timestamp;

	while (1)
	{
		if (!check_simulation_status(philo))
			break ;
		take_left_fork(philo);
		take_right_fork(philo);
		start_eating(philo);
		usleep(philo->arguments->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		timestamp = get_timestamp(philo);
		print_status(philo, "is sleeping", timestamp);
		usleep(philo->arguments->time_to_sleep * 1000);
		timestamp = get_timestamp(philo);
		print_status(philo, "is thinking", timestamp);
	}
}

static void	even_philosopher_routine(t_philo *philo)
{
	int	timestamp;

	usleep(1000);
	while (1)
	{
		if (!check_simulation_status(philo))
			break ;
		take_right_fork(philo);
		take_left_fork(philo);
		start_eating(philo);
		usleep(philo->arguments->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		timestamp = get_timestamp(philo);
		print_status(philo, "is sleeping", timestamp);
		usleep(philo->arguments->time_to_sleep * 1000);
		timestamp = get_timestamp(philo);
		print_status(philo, "is thinking", timestamp);
	}
}

static void	single_philosopher_routine(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp(philo);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork", timestamp);
	while (check_simulation_status(philo))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
}

void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->arguments->number_of_philosphers == 1)
		single_philosopher_routine(philo);
	else if (philo->philosopher_id % 2 == 1)
		odd_philosopher_routine(philo);
	else
		even_philosopher_routine(philo);
	return (NULL);
}
