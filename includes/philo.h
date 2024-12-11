/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:42:57 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/10 14:23:31 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
    pthread_t   thread;
    int id;
    int dead;
    int times_eaten;
    int started_eating;
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *death;
    pthread_mutex_t *print;
    //time since started eating???
}   t_philo;

typedef struct s_all
{
    t_philo *philos;
    int num_of_philos;
    int dead;
    int must_eat;
    pthread_mutex_t death;
    pthread_mutex_t print;
    pthread_mutex_t *forks;
    //mutexes here???
}   t_all;

//philo.c
int philo(t_all *a);
void    free_destroy_all(t_all *a);

//init.c
int init_mutexes(t_all *a);
void    initialize(t_all *a, char **argv);

//threads.c
int create_threads(t_all *a);
void    join_threads(t_all *a);

//activities.c
void   *eat_sleep_think(void *p);
void    print_state(t_philo *philo, char *str);
unsigned long    get_time();

#endif