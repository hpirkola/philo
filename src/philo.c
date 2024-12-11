/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:22:19 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/10 14:23:13 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    free_destroy_all(t_all *a)
{
    int i;

    i = 0;
    while (i < a->num_of_philos)
    {
        pthread_mutex_destroy(a->philos[i].left_fork);
        pthread_mutex_destroy(a->philos[i].right_fork);
        pthread_mutex_destroy(a->philos[i].death);
        pthread_mutex_destroy(a->philos[i].print);
        i++;
    }
    free(a->philos);
}

int someone_is_dead(t_all *a)
{
    int i;

    i = 0;
    while (i < a->num_of_philos)
    {
        if (get_time() - a->philos[i].started_eating >= a->philos[i].time_to_die)
        {
            pthread_mutex_lock(&a->death);
            a->dead = 1;
            pthread_mutex_unlock(&a->death);
            print_state(&a->philos[i], "died");
            return (1);
        }
        i++;
    }
    return (0);
}

int all_have_eaten(t_all *a)
{
    int i;

    i = 0;
    if (a->must_eat == 0)
        return (0);
    while (i < a->num_of_philos)
    {
        if (a->philos[i].times_eaten < a->must_eat)
            return (0);
        i++;
    }
    return (1);
}

void    monitor(t_all *a)
{
    while (1)
    {
        if (someone_is_dead(a))
            return ;
        if (all_have_eaten(a))
            return ;
    }
}

int    philo(t_all *a)
{
    if (!create_threads(a))
    {
        write(2, "Creating threads failed\n", 24);
        return (0);
    }
    monitor(a);
    join_threads(a);
    free_destroy_all(a);
    return (1);
}