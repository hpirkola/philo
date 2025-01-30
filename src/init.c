/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:29:17 by hpirkola          #+#    #+#             */
/*   Updated: 2025/01/30 11:24:45 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	destroy_mutexes(t_all *a, int i)
{
	pthread_mutex_destroy(&a->death);
	pthread_mutex_destroy(&a->print);
	while (i >= 0)
	{
		pthread_mutex_destroy(&a->forks[i]);
		pthread_mutex_destroy(&a->philos[i].eaten);
		i--;
	}
	return (0);
}

int	init_mutexes(t_all *a)
{
	int	i;

	if (pthread_mutex_init(&a->death, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&a->print, NULL) != 0)
		return (pthread_mutex_destroy(&a->death), 0);
	i = 0;
	while (i < a->num_of_philos)
	{
		if (pthread_mutex_init(&a->forks[i], NULL) != 0)
			return (destroy_mutexes(a, i));
		if (pthread_mutex_init(&a->philos[i].eaten, NULL) != 0)
		{
			pthread_mutex_destroy(&a->forks[i--]);
			return (destroy_mutexes(a, i));
		}
		i++;
	}
	return (1);
}

void	initialize(t_all *a, char **argv)
{
	int	i;

	a->dead = 0;
	if (argv[5])
		a->must_eat = ft_atoi(argv[5]);
	else
		a->must_eat = 0;
	i = -1;
	while (++i < a->num_of_philos)
	{
		a->philos[i].id = i + 1;
		a->philos[i].num_of_philos = a->num_of_philos;
		a->philos[i].time_to_die = ft_atoi(argv[2]);
		a->philos[i].time_to_eat = ft_atoi(argv[3]);
		a->philos[i].time_to_sleep = ft_atoi(argv[4]);
		a->philos[i].dead = &a->dead;
		a->philos[i].times_eaten = 0;
		a->philos[i].left_fork = &a->forks[i];
		if (i + 1 < a->num_of_philos)
			a->philos[i].right_fork = &a->forks[i + 1];
		else
			a->philos[i].right_fork = &a->forks[0];
		a->philos[i].death = &a->death;
		a->philos[i].print = &a->print;
	}
}
