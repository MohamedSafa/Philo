/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/28 22:02:58 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_arguments	arguments;
	t_philo		*philosophers;
	int			i;

	if (!validate_input(argc, argv))
	{
		write(1, "Arguments not valid!", 21);
		return (1);
	}
	parse_arguments(argv, &arguments);
	if (!init_data(&arguments, &philosophers))
		return (1);
	start_dining(&arguments, philosophers);
	i = 0;
	while (i < arguments.number_of_philosphers)
	{
		pthread_join(arguments.threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&arguments.print_mutex);
	pthread_mutex_destroy(&arguments.death_mutex);
	free(arguments.threads);
	free(arguments.forks);
	free(philosophers);
	return (0);
}
