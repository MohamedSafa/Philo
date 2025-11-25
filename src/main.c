/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:39:57 by msafa             #+#    #+#             */
/*   Updated: 2025/11/25 01:37:52 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int	main(int argc, char *argv[])
{
	t_arguments arguments;
	t_philo *philosophers;
	pthread_mutex_t *forks;
	pthread_t *threads;
	int i;

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
	threads = init_threads(&arguments,&philosophers,forks);
	if(threads == NULL)
		return(1);
	while(i < arguments.number_of_philosphers)
	{
		void *ret;
		if((philosophers[i]).last_meal_time > arguments.time_to_die)
		{
			pthread_join(threads[i],&ret);
			return(0);
		}
		i++;
	}
	return (0);
}
