/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:04:16 by hpirkola          #+#    #+#             */
/*   Updated: 2025/02/17 15:12:00 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	long			sec;
	long			m_sec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec;
	m_sec = time.tv_usec;
	return (sec * 1000 + m_sec / 1000);
}

int	get_death(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(philo->death);
	if (*philo->dead == 1)
		dead = 1;
	pthread_mutex_unlock(philo->death);
	return (dead);
}

void	print_state(t_philo *philo, char *str, char *color)
{
	bool	check;

	pthread_mutex_lock(philo->death);
	check = *philo->dead;
	if (!check)
	{
		pthread_mutex_lock(philo->print);
		printf("%s", color);
		printf("%lu %d %s\n"RESET, get_time() - philo->start, philo->id, str);
		pthread_mutex_unlock(philo->print);
		pthread_mutex_unlock(philo->death);
	}
	else
		pthread_mutex_unlock(philo->death);
}
