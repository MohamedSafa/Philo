/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:53:28 by msafa             #+#    #+#             */
/*   Updated: 2025/10/30 17:50:00 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1. What is a mutex:
A mutex is a short for mutual exclusion so it is the key to a shared resource. In this project, only one philosopher
can hold the key (Fork) at a time. So if another philosopher can hold the key (fork) at a time.
So mutexes prevent two philosophers (threads) from grabbing the same fork simultaneously, which would cause a data race.

1. P_thread_mutex_init:

    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
    
Create (initialize) a mutex before using it

2. P_thread_mutex_lock:

int pthread_mutex_lock(pthread_mutex_t *mutex);

Lock the mutex — block if someone else already locked it.

3. P_thread_mutex_unlock:

int pthread_mutex_unlock(pthread_mutex_t *mutex);

Unlock the mutex so others can use it.

4.P_thread_mutex_destroy:

int pthread_mutex_destroy(pthread_mutex_t *mutex);

Clean up the mutex when you’re done.

*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        usleep(1000);

        // take forks (lock)
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);

        printf("Philosopher %d is eating\n", id);
        usleep(1000);

        // put forks back (unlock)
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);

        printf("Philosopher %d is sleeping\n", id);
        usleep(1000);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_init(&forks[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}
