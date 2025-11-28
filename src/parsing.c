/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:20:48 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:08:12 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	only_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	validate_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (i < argc)
	{
		if (!argv[i] || !argv[i][0])
			return (0);
		if (!only_digits(argv[i]))
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
	if (argv[5])
		arguments->number_of_meals = atoi(argv[5]);
	else
		arguments->number_of_meals = -1;
}
