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
    bool    check;

    pthread_mutex_lock(philo->death);
    check = *philo->dead;
    pthread_mutex_unlock(philo->death);
    if (!check)
    {
        pthread_mutex_lock(philo->print);
        //print the time + which philo + what is it doing
        printf("%lu %d %s\n", get_time(), philo->id, str);
        pthread_mutex_unlock(philo->print);
    }
}

int    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(philo, "has taken a fork");
    pthread_mutex_lock(philo->death);
    if (*(philo->dead))
    {
        pthread_mutex_unlock(philo->death);
        pthread_mutex_unlock(philo->left_fork);
        return (0);
    }
    pthread_mutex_unlock(philo->death);
    pthread_mutex_lock(philo->right_fork);
    print_state(philo, "has taken a fork");
    //mark the time the philo started eating
    pthread_mutex_lock(&philo->eaten);
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->eaten);
    philo->started_eating = get_time();
    print_state(philo, "is eating");
    if (!doing_stuff(philo, philo->time_to_eat))
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        return (0);
    }
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (1);
}

int    doing_stuff(t_philo *philo, int n)
{
    //make them sleep a->time_to_sleep amount
    unsigned long   stop;

    stop = get_time() + n;
    while (get_time() < stop)
    {
        usleep(250);
        pthread_mutex_lock(philo->death);
        if (*(philo->dead))
        {
            pthread_mutex_unlock(philo->death);
            return (0) ;
        }
        pthread_mutex_unlock(philo->death);
    }
    return (1);
}

void    one_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->death);
    *philo->dead = 1;
    pthread_mutex_unlock(philo->death);
    pthread_mutex_unlock(philo->left_fork);
}

void    *eat_sleep_think(void *p)
{
    t_philo *philo;

    philo = (t_philo *) p;
    //philo->started_eating = get_time();
    //check if there is only one philo
    //delay evens and the last philo
    if (philo->num_of_philos == 1)
    {
        one_philo(philo);
        return (NULL);
    }
    if (philo->id % 2 == 0 || philo->id == philo->num_of_philos)
        usleep(philo->time_to_eat / 2);
    //ussleep if the amout of philos % 2 == 0?
    //printf("%d\n", *philo->dead);
    while (!*philo->dead)
    {
        print_state(philo, "is thinking");
        if (!eat(philo))
            break ;
        print_state(philo, "is sleeping");
        if (!doing_stuff(philo, philo->time_to_sleep))
            break ;
    }
    return (NULL);
}