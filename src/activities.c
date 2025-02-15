/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:11:21 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/15 16:12:11 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(philo->death);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->death);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_unlock(philo->death);
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken a fork", GREEN);
	pthread_mutex_lock(&philo->eaten);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eaten);
	pthread_mutex_lock(&philo->started);
	philo->started_eating = get_time();
	pthread_mutex_unlock(&philo->started);
	print_state(philo, "is eating", YELLOW);
	if (!doing_stuff(philo, philo->time_to_eat))
		return (unlock_forks(philo), 0);
	unlock_forks(philo);
	return (1);
}

int	doing_stuff(t_philo *philo, int n)
{
	unsigned long	stop;

	stop = get_time() + n;
	while (get_time() < stop)
	{
		usleep(250);
		pthread_mutex_lock(philo->death);
		if (*(philo->dead))
		{
			pthread_mutex_unlock(philo->death);
			return (0);
		}
		pthread_mutex_unlock(philo->death);
	}
	return (1);
}

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->death);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->death);
	pthread_mutex_unlock(philo->left_fork);
}

void	*eat_sleep_think(void *p)
{
	t_philo			*philo;
	struct timeval	time;

	philo = (t_philo *) p;
	if (philo->num_of_philos == 1)
		return (one_philo(philo), NULL);
	if (philo->id % 2 == 0 || philo->id == philo->num_of_philos)
	{
		gettimeofday(&time, NULL);
		usleep((time.tv_usec % 3000) + 1000);
	}
	while (!get_death(philo))
	{
		print_state(philo, "is thinking", PURPLE);
		if (!eat(philo))
			break ;
		print_state(philo, "is sleeping", BLUE);
		if (!doing_stuff(philo, philo->time_to_sleep))
			break ;
		gettimeofday(&time, NULL);
		usleep((time.tv_usec % 3000) + 1000);
	}
	return (NULL);
}
