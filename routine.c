/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:42:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:08:52 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork_and_print(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork[id]);
	print_action(data, FORK, id, ft_get_time(&data->time, data));
}

void	unlock_fork_and_print(t_data *data, int id)
{
	pthread_mutex_unlock(&data->fork[id]);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));
}

void	handle_last_philosopher(t_data *data, int id, t_bool *both)
{
	pthread_mutex_lock(&data->fork[id]);
	print_action(data, FORK, id, ft_get_time(&data->time, data));

	pthread_mutex_lock(&data->fork[0]);
	print_action(data, FORK, id, ft_get_time(&data->time, data));
	get_food(data, id);
	
	pthread_mutex_unlock(&data->fork[0]);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));

	pthread_mutex_unlock(&data->fork[id]);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));
	
	

	*both = TRUE;
	think_and_die(data, id, *both);
}

void handle_philosophers(t_data *data, int id, t_bool *both)
{
    int first_fork = id;
    int second_fork = (id + 1) % data->nb_fork;

    if (first_fork > second_fork) {
        int temp = first_fork;
        first_fork = second_fork;
        second_fork = temp;
    }

    pthread_mutex_lock(&data->fork[first_fork]);
    print_action(data, FORK, id, ft_get_time(&data->time, data));

    pthread_mutex_lock(&data->fork[second_fork]);
    print_action(data, FORK, id, ft_get_time(&data->time, data));
    get_food(data, id);

    pthread_mutex_unlock(&data->fork[second_fork]);
    print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));

    pthread_mutex_unlock(&data->fork[first_fork]);
    print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));

    *both = TRUE;
    think_and_die(data, id, *both);
}

void	*routine(void *d)
{
	t_data		*data;
	t_data_id	*all;
	t_bool		both;
	int			id;

	all = (t_data_id *)d;
	id = all->id;
	data = all->data;
	free(all);
	if (data->nb_fork == 1)
		return (highlander(data, id));
	odd_wait(id, data);
	while (go_on_change(data, FALSE) == TRUE)
	{
		both = FALSE;
		//lock_fork_and_print(data, id);
		handle_philosophers(data, id, &both);
	}
	
	return (NULL);
}
