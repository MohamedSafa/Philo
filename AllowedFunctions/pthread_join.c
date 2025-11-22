/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:07:20 by msafa             #+#    #+#             */
/*   Updated: 2025/10/30 16:50:29 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. Definition:
    - Used to wait for a thread to finish
    - It ensures the main program (or another thread) doesn’t continue until the target thread is done.
    - It also allows you to retrieve the thread’s return value if needed.

    So we would use pthread_join in order for the main program to wait for all philosophers to finish eating or the simulation to end before exiting that's why
    it blocks the main program.
    
2. Syntax : 
    #include <pthread.h>

    int pthread_join(pthread_t thread, void **retval);

    So now we can blocks the calling thread until the target thread terminates.
    Cleans up thread resources (so you don’t leak memory).
    You can retrieve the value returned by the thread function.

*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 3

void *philosopher(void *arg) {
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);
    usleep(1000);
    printf("Philosopher %d is eating\n", id);
    usleep(1000);

    return (void *)(long)id; // return philosopher ID
}

int main(void) {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        void *ret;
        pthread_join(threads[i], &ret); // wait for thread to finish
        printf("Philosopher %ld has finished\n", (long)ret);
    }

    return 0;
}
