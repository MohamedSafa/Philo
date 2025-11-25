/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:28:31 by msafa             #+#    #+#             */
/*   Updated: 2025/11/25 01:33:18 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *dining(void *arg)
{
    t_philo *philosophers;
    struct timeval t;
    int timestamp;
    int start_time;

    philosophers = (t_philo *)arg;
    gettimeofday(&t,NULL);
    start_time = t.tv_sec;
    timestamp = 0;
    if(philosophers->philosopher_id % 2 == 1)
    {
        while(1)
        {
            pthread_mutex_lock(philosophers->left_fork);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            pthread_mutex_lock(philosophers->right_fork);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            philosophers->last_meal_time = timestamp;
            printf("%d %d is eating\n", timestamp,philosophers->philosopher_id);
            usleep(philosophers->arguments->time_to_eat * 1000);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            pthread_mutex_unlock(philosophers->left_fork);
            pthread_mutex_unlock(philosophers->right_fork);
            printf("%d %d is sleeping\n",timestamp,philosophers->philosopher_id);
            usleep(philosophers->arguments->time_to_sleep * 1000);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            printf("%d %d is thinking\n",timestamp,philosophers->philosopher_id);
        }
    }
    else
    {
        while(1)
        {
            pthread_mutex_lock(philosophers->right_fork);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            pthread_mutex_lock(philosophers->left_fork);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            philosophers->last_meal_time = timestamp;
            printf("%d %d is eating\n", timestamp,philosophers->philosopher_id);
            usleep(philosophers->arguments->time_to_eat * 1000);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            pthread_mutex_unlock(philosophers->left_fork);
            pthread_mutex_unlock(philosophers->right_fork);
            printf("%d %d is sleeping\n",timestamp,philosophers->philosopher_id);
            usleep(philosophers->arguments->time_to_sleep * 1000);
            gettimeofday(&t,NULL);
            timestamp = (t.tv_sec - start_time) * 1000;
            printf("%d %d is thinking\n",timestamp,philosophers->philosopher_id);
        }
    }
    return NULL ;
}
