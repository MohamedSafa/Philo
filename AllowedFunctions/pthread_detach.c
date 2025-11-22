/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_detach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:48:00 by msafa             #+#    #+#             */
/*   Updated: 2025/10/30 17:30:50 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Definition: pthread_detach is used to detach a thread from the main program

2. Syntax : 

#include <pthread.h>

int pthread_detach(pthread_t thread);

So we use it if we don't want for the thread to finish , don't want to know the result of the thread, don't responsible for cleaning. So in philo, i need to check 
if the philo died or not so i shouldn't detach them.

*/