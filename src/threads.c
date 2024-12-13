/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:28:52 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/10 13:03:37 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int create_threads(t_all *a)
{
    int i;
    int j;
    
    i = 0;
    while (i < a->num_of_philos)
    {
        a->philos[i].started_eating = get_time();
        if (pthread_create(&a->philos[i].thread, NULL, eat_sleep_think, (void *)&a->philos[i]) != 0)
        {
            //creating thread failed
            pthread_mutex_lock(&a->death);
            a->dead = 1;
            pthread_mutex_unlock(&a->death);
            j = 0;
            while (j <= i)
            {
                pthread_join(a->philos[j].thread, NULL);
                j++;
            }
            free_destroy_all(a);
            return (0);
        }
        i++;
    }
    return (1);    
}

void    join_threads(t_all *a)
{
    int i;

    i = 0;
    while (i < a->num_of_philos)
    {
        pthread_join(a->philos[i].thread, NULL);
        i++;
    }
}