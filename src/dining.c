/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:28:31 by msafa             #+#    #+#             */
/*   Updated: 2025/11/27 21:24:09 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *dining(void *arg)
{
    t_philo *philosophers;
    struct timeval t;
    int timestamp;

    philosophers = (t_philo *)arg;
    timestamp = 0;
    if(philosophers->philosopher_id % 2 == 1)
    {
        while(1)
        {
            pthread_mutex_lock(philosophers->left_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            pthread_mutex_lock(philosophers->right_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            pthread_mutex_lock(&philosophers->meal_mutex);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            philosophers->last_meal_time = timestamp;
            philosophers->meals_eaten++;
            pthread_mutex_unlock(&philosophers->meal_mutex);
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is eating\n", timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            usleep(philosophers->arguments->time_to_eat * 1000 * 0.9);
            pthread_mutex_unlock(philosophers->left_fork);
            pthread_mutex_unlock(philosophers->right_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is sleeping\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            usleep(philosophers->arguments->time_to_sleep * 1000);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is thinking\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
        }
    }
    else
    {
        usleep(1000);
        while(1)
        {
            pthread_mutex_lock(philosophers->right_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            pthread_mutex_lock(philosophers->left_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d has taken a fork\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->meal_mutex);
            philosophers->last_meal_time = timestamp;
            philosophers->meals_eaten++;
            pthread_mutex_unlock(&philosophers->meal_mutex);
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is eating\n", timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            usleep(philosophers->arguments->time_to_eat * 1000 * 0.9);
            pthread_mutex_unlock(philosophers->left_fork);
            pthread_mutex_unlock(philosophers->right_fork);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is sleeping\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
            usleep(philosophers->arguments->time_to_sleep * 1000);
            gettimeofday(&t,NULL);
            timestamp = ((t.tv_sec * 1000)+ (t.tv_usec / 1000)) - philosophers->arguments->start_time;
            pthread_mutex_lock(&philosophers->arguments->print_mutex);
            printf("%d %d is thinking\n",timestamp,philosophers->philosopher_id);
            pthread_mutex_unlock(&philosophers->arguments->print_mutex);
        }
    }
    return NULL ;
}
