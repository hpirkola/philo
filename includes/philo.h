/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:42:57 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/13 14:58:40 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define RESET "\033[0;39m"

typedef struct s_philo
{
	size_t			start;
	pthread_t		thread;
	int				num_of_philos;
	int				id;
	int				*dead;
	int				times_eaten;
	size_t			started_eating;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
	pthread_mutex_t	eaten;
	pthread_mutex_t	started;
}	t_philo;

typedef struct s_all
{
	t_philo			*philos;
	int				num_of_philos;
	int				dead;
	int				must_eat;
	size_t			start;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_all;

//philo.c
int				philo(t_all *a);
void			free_destroy_all(t_all *a);

//init.c
int				init_mutexes(t_all *a);
void			initialize(t_all *a, char **argv);

//threads.c
int				create_threads(t_all *a);
void			join_threads(t_all *a);

//activities.c
void			*eat_sleep_think(void *p);
int				doing_stuff(t_philo *philo, int n);

//ft_atoi.c
int				ft_atoi(const char *str);

//utils.c
int				get_death(t_philo *philo);
unsigned long	get_time(void);
void			print_state(t_philo *philo, char *str, char *color);

#endif
