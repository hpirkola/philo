/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:04:16 by hpirkola          #+#    #+#             */
/*   Updated: 2025/01/30 11:06:17 by hpirkola         ###   ########.fr       */
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

void	print_state(t_philo *philo, char *str)
{
	bool	check;

	pthread_mutex_lock(philo->death);
	check = *philo->dead;
	pthread_mutex_unlock(philo->death);
	if (!check)
	{
		pthread_mutex_lock(philo->print);
		printf("%lu %d %s\n", get_time(), philo->id, str);
		pthread_mutex_unlock(philo->print);
	}
}
