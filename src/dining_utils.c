/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:00:00 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:05:37 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *msg, int timestamp)
{
	pthread_mutex_lock(&philo->arguments->print_mutex);
	pthread_mutex_lock(&philo->arguments->death_mutex);
	if (philo->arguments->simulation_running)
		printf("%d %d %s\n", timestamp, philo->philosopher_id, msg);
	pthread_mutex_unlock(&philo->arguments->death_mutex);
	pthread_mutex_unlock(&philo->arguments->print_mutex);
}

int	get_timestamp(t_philo *philo)
{
	struct timeval	t;
	int				timestamp;

	gettimeofday(&t, NULL);
	timestamp = ((t.tv_sec * 1000) + (t.tv_usec / 1000))
		- philo->arguments->start_time;
	return (timestamp);
}

void	take_left_fork(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(philo->left_fork);
	timestamp = get_timestamp(philo);
	print_status(philo, "has taken a fork", timestamp);
}

void	take_right_fork(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(philo->right_fork);
	timestamp = get_timestamp(philo);
	print_status(philo, "has taken a fork", timestamp);
}

void	start_eating(t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->meal_mutex);
	timestamp = get_timestamp(philo);
	philo->last_meal_time = timestamp;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating", timestamp);
}
