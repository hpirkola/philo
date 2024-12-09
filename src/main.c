/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:02:48 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/09 16:00:01 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    initialize(t_all *a, char **argv)
{
    int i;

    a->num_of_philos = atoi(argv[1]); //CHANGE TO FT_ATOI!!!
    a->dead = 0;
    i = 0;
    while (i < a->num_of_philos)
    {
        a->philos[i].id = i + 1;
        a->philos[i].time_to_die = atoi(argv[2]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_eat = atoi(argv[3]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_sleep = atoi(argv[4]); // CHANGE TO FT_ATOI
        a->philos[i].dead = 0;
        i++;
    }
}

int check_input(int argc, char **argv)
{
    int i;
    if (argc < 5 || argc > 6)
        return (0);
    //check if every argument is numeric with ft_atoi
    i = 0;
    while (argv[++i])
    {
        if (atoi(argv[i]) == 0) //CHANGE TO FT_ATOI!!!
        {
            if (i != 5 || (i == 5 && argv[i][0] != '0'))
                return (0);
        }
    }
    //check that the amount of philos is max 200
    if (atoi(argv[1]) > 200) //CHANGE TO FT_ATOI!!!
        return (0);
    return (1);    
}

int main(int argc, char **argv)
{
    t_all   table;
    if (!check_input(argc, argv))
        return (write(2, "Invalid input\n", 14));
    //allocate memory
    initialize(&table, argv);
    if (!create_threads(&table))
        return (write(2, "Creating threads failed\n", 24));
    join_threads();
    //free memory and destroy mutexes
    return (0);
}