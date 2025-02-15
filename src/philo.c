/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:22:19 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/15 16:20:24 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_destroy_all(t_all *a)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&a->death);
	pthread_mutex_destroy(&a->print);
	while (i < a->num_of_philos)
	{
		pthread_mutex_destroy(&a->forks[i]);
		pthread_mutex_destroy(&a->philos[i].eaten);
		i++;
	}
	free(a->philos);
}

int	someone_is_dead(t_all *a)
{
	int	i;

	i = 0;
	while (i < a->num_of_philos)
	{
		pthread_mutex_lock(&a->philos[i].started);
		if (get_time() - a->philos[i].started_eating >= \
				a->philos[i].time_to_die)
		{
			pthread_mutex_unlock(&a->philos[i].started);
			pthread_mutex_lock(a->philos[i].death);
			a->dead = 1;
			pthread_mutex_unlock(a->philos[i].death);
			pthread_mutex_lock(a->philos[i].print);
			printf(RED);
			printf("%lu %d died\n"RESET, get_time() - a->start, a->philos[i].id);
			pthread_mutex_unlock(a->philos[i].print);
			return (1);
		}
		else
			pthread_mutex_unlock(&a->philos[i].started);
		i++;
	}
	return (0);
}

int	all_have_eaten(t_all *a)
{
	int	i;

	i = 0;
	if (a->must_eat == 0)
		return (0);
	while (i < a->num_of_philos)
	{
		pthread_mutex_lock(&a->philos[i].eaten);
		if (a->philos[i].times_eaten < a->must_eat)
		{
			pthread_mutex_unlock(&a->philos[i].eaten);
			return (0);
		}
		pthread_mutex_unlock(&a->philos[i].eaten);
		i++;
	}
	pthread_mutex_lock(&a->death);
	a->dead = 1;
	pthread_mutex_unlock(&a->death);
	return (1);
}

void	monitor(t_all *a)
{
	while (1)
	{
		if (someone_is_dead(a))
			return ;
		if (all_have_eaten(a))
			return ;
	}
}

int	philo(t_all *a)
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
