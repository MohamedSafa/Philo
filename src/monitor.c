/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:00:00 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:08:12 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_death(t_arguments *arguments, t_philo *philosophers, int i,
		int current_time)
{
	int	death_tracker;

	pthread_mutex_lock(&philosophers[i].meal_mutex);
	death_tracker = philosophers[i].last_meal_time;
	if ((current_time - death_tracker) > arguments->time_to_die)
	{
		pthread_mutex_unlock(&philosophers[i].meal_mutex);
		pthread_mutex_lock(&arguments->death_mutex);
		arguments->simulation_running = 0;
		pthread_mutex_unlock(&arguments->death_mutex);
		pthread_mutex_lock(&arguments->print_mutex);
		printf("%d %d died\n", current_time, philosophers[i].philosopher_id);
		pthread_mutex_unlock(&arguments->print_mutex);
	}
	else
		pthread_mutex_unlock(&philosophers[i].meal_mutex);
}

static int	check_meals_finished(t_arguments *arguments, t_philo *philosophers)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	while (i < arguments->number_of_philosphers)
	{
		pthread_mutex_lock(&philosophers[i].meal_mutex);
		if (arguments->number_of_meals != -1
			&& philosophers[i].meals_eaten >= arguments->number_of_meals)
			finished_count++;
		pthread_mutex_unlock(&philosophers[i].meal_mutex);
		i++;
	}
	return (finished_count);
}

void	start_dining(t_arguments *arguments, t_philo *philosophers)
{
	int	i;
	int	current_time;
	int	finished_count;

	while (1)
	{
		usleep(1000);
		i = 0;
		while (i < arguments->number_of_philosphers)
		{
			current_time = get_current_time() - arguments->start_time;
			check_death(arguments, philosophers, i, current_time);
			if (!arguments->simulation_running)
				return ;
			i++;
		}
		finished_count = check_meals_finished(arguments, philosophers);
		if (finished_count == arguments->number_of_philosphers)
		{
			pthread_mutex_lock(&arguments->death_mutex);
			arguments->simulation_running = 0;
			pthread_mutex_unlock(&arguments->death_mutex);
			return ;
		}
	}
}
