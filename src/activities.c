/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:11:21 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/10 14:30:34 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long    get_time()
{
    struct timeval time;
    long    sec;
    long    m_sec;

    gettimeofday(&time, NULL);
    sec = time.tv_sec; // seconds
    m_sec = time.tv_usec; // mikroseconds

    return (sec * 1000 + m_sec / 1000);
}

void    print_state(t_philo *philo, char *str)
{
        (void)str;
        pthread_mutex_lock(philo->print);
        //print the time + which philo + what is it doing
        printf("%lu %d %s\n", get_time(), philo->id, str);
        pthread_mutex_unlock(philo->print);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    //mark the time the philo started eating
    philo->times_eaten++;
    philo->started_eating = get_time();
    print_state(philo, "is eating");
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void    sleeping(t_philo *philo)
{
    //make them sleep a->time_to_sleep amount
    unsigned long   stop;

    stop = get_time() + philo->time_to_sleep;
    while (get_time() < stop)
        usleep(250);    
}

void    *eat_sleep_think(void *p)
{
    t_philo *philo;
    //while loop to go throught the activities
    philo = (t_philo *) p;
    //check if there is only one philo
    //ussleep if the amout of philos % 2 == 0?
    while (!philo->dead)
    {
        print_state(philo, "is thinking");
        eat(philo);
        print_state(philo, "is sleeping");
        sleeping(philo);
    }
    return (NULL);
}