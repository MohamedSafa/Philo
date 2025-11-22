/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:40:12 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 11:59:55 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. It starts a new thread that runs a function concurrently(same time) with the main program.
    It creates a new thread in a C program.
    In philosophers each philosopher will be represented as a seperate thread allowing them to eat , drink and sleep simultaneously 

2. Syntax :  
#include <pthread.h>

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
where : 
    pthread_t *thread: pointer to a thread identifier that will store the new thread’s ID.

    const pthread_attr_t *attr: thread attributes (usually NULL for default attributes).

    void *(*start_routine)(void *): pointer to the function the thread will execute. Must return void * and take a single void * argument.

    void *arg: argument passed to the thread function.


*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

void *philosopher(void *arg) {
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);
    usleep(1000);  // simulate thinking
    printf("Philosopher %d is eating\n", id);
    usleep(1000);  // simulate eating

    return NULL;
}

int main(void) {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    int i;

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
