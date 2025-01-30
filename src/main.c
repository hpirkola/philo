/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:02:48 by hpirkola          #+#    #+#             */
/*   Updated: 2025/01/30 11:10:45 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	allocation(t_all *a)
{
	a->philos = malloc(sizeof(t_philo) * a->num_of_philos + 1);
	if (!a->philos)
		return (0);
	a->forks = malloc(sizeof(pthread_mutex_t) * a->num_of_philos);
	return (1);
}

int	check_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	while (argv[++i])
	{
		if (ft_atoi(argv[i]) == 0)
		{
			if (i != 5 || (i == 5 && argv[i][0] != '0'))
				return (0);
		}
	}
	if (ft_atoi(argv[1]) > 200)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_all	table;

	if (!check_input(argc, argv))
	{
		write(2, "Invalid input\n", 14);
		return (1);
	}
	table.num_of_philos = ft_atoi(argv[1]);
	if (!allocation(&table))
	{
		write(2, "Allocation fail\n", 16);
		return (1);
	}
	if (!init_mutexes(&table))
	{
		free(table.philos);
		free(table.forks);
		write(2, "Mutex creation fail\n", 20);
		return (1);
	}
	initialize(&table, argv);
	if (!philo(&table))
		return (1);
	return (0);
}
