/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msafa <msafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:25:59 by msafa             #+#    #+#             */
/*   Updated: 2025/10/13 11:39:48 by msafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

1. gettimeofday gets the current time with microsecond precision since unix epoch 1970-01-01 00:00:00 UTC
2. 
struct timeval{
    time_t tv_sec;
    suseconds_t tv_usec; // is the microseconds part of the seconds returned form the function
};

3. Syntax : int gettimeofday(struct timeval *tv,struct timezone *tz);
Here timezone will be set to NULL


*/

#include <sys/time.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);

    time_t now = t.tv_sec;
    struct tm *local = localtime(&now); // convert to local time

    printf("Current time: %d:%d:%d\n",
           local->tm_hour,
           local->tm_min,
           local->tm_sec);

    return 0;
}

