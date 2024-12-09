/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpirkola <hpirkola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:02:48 by hpirkola          #+#    #+#             */
/*   Updated: 2024/12/09 22:05:02 by hpirkola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    initialize(t_all *a, char **argv)
{
    int i;

    a->dead = 0;
    if (argv[5])
        a->must_eat = atoi(argv[5]); // CHANGE TO FT_ATOI !!!
    else
        a->must_eat = 0;
    i = 0;
    while (i < a->num_of_philos)
    {
        a->philos[i].id = i + 1;
        a->philos[i].time_to_die = atoi(argv[2]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_eat = atoi(argv[3]); // CHANGE TO FT_ATOI
        a->philos[i].time_to_sleep = atoi(argv[4]); // CHANGE TO FT_ATOI
        a->philos[i].dead = 0;
        pthread_mutex_init(a->philos[i].left_fork, NULL);
        pthread_mutex_init(a->philos[i].right_fork, NULL);
        pthread_mutex_init(a->philos[i].death, NULL);
        pthread_mutex_init(a->philos[i].print, NULL);
        i++;
    }
}

int allocation(t_all *a)
{
    a->philos = malloc(sizeof(t_philo) * a->num_of_philos + 1);
    if (!a->philos)
        return (0);
    return (1);
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

void    free_destroy_all(t_all *a)
{
    int i;

    i = 0;
    while (i < a->num_of_philos)
    {
        pthread_mutex_destroy(a->philos[i].left_fork);
        pthread_mutex_destroy(a->philos[i].right_fork);
        pthread_mutex_destroy(a->philos[i].death);
        pthread_mutex_destroy(a->philos[i].print);
        i++;
    }
    free(a->philos);
}

int main(int argc, char **argv)
{
    t_all   table;
    
    if (!check_input(argc, argv))
        return (write(2, "Invalid input\n", 14));
    table.num_of_philos = atoi(argv[1]); //CHANGE TO FT_ATOI !!!
    if (!allocation(&table))
        return (write(2, "Allocation fail\n", 16));
    initialize(&table, argv);
    if (!create_threads(&table))
        return (write(2, "Creating threads failed\n", 24));
    join_threads(&table);
    free_destroy_all(&table);
    return (0);
}