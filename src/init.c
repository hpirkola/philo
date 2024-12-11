/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:29:17 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/10 13:28:21 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int init_mutexes(t_all *a)
{
    int i;
    
    //handle mutex fails
    pthread_mutex_init(&a->death, NULL);
    pthread_mutex_init(&a->print, NULL);
    i = 0;
    while (i < a->num_of_philos)
    {
        pthread_mutex_init(&a->forks[i], NULL);
        i++;
    }
    return (1);    
}

void    initialize(t_all *a, char **argv)
{
    int i;

    a->dead = 0;
    if (argv[5])
        a->must_eat = atoi(argv[5]); // CHANGE TO FT_ATOI !!!
    else
        a->must_eat = 0;
    i = 0;
    while (i < a->num_of_philos)
    {
        a->philos[i].id = i + 1;
        a->philos[i].time_to_die = atoi(argv[2]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_eat = atoi(argv[3]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_sleep = atoi(argv[4]); // CHANGE TO FT_ATOI
        a->philos[i].dead = 0;
        a->philos[i].times_eaten = 0;
        a->philos[i].left_fork = &a->forks[i];
        if (i + 1 < a->num_of_philos)
            a->philos[i].right_fork = &a->forks[i + 1];
        else
            a->philos[i].right_fork = &a->forks[0];
        a->philos[i].death = &a->death;
        a->philos[i].print = &a->print;
        i++;
    }
}