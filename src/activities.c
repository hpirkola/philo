/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:11:21 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/09 22:09:21 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    print_state(t_philo philo, char *str)
{
        (void)str;
        pthread_mutex_lock(philo.print);
        //print the time + which philo + what is it doing
        pthread_mutex_unlock(philo.print);
}

void    *eat_sleep_think()
{
    return (NULL);
}