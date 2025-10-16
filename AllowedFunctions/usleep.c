/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:13:33 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 11:25:23 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. usleep(usec) pauses the current thread for a given number of microseconds.
2. header: unistd.h
3. Returns 0 on success & -1 on error (e.g, interrupted by a signal)
4. Syntax : int usleep(useconds_t usec); useconds is an unsigned integer type holds integers in the range
    [0,1000000]
5. Will be used in PHILO to control timing of sleeping,eating & thinking.
6. 1 SECOND = 1,000,000 MICROSECONDS

*/

                        // A whole process
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Start\n");
    usleep(2000000);
    printf("2 seconds later\n");

    usleep(4000000);
    printf("4 seconds later\n");

    return 0;
}
                        // a single thread inside the main thread 

// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// void *worker(void *arg)
// {
//     printf("Worker: sleeping 2s\n");
//     usleep(2000000);
//     printf("Worker: awake\n");
//     return NULL;
// }

// int main(void)
// {
//     pthread_t t;
//     pthread_create(&t, NULL, worker, NULL);

//     printf("Main: running while worker sleeps\n");
//     usleep(1000000);
//     printf("Main: still running\n");

//     pthread_join(t, NULL);
//     return 0;
// }
