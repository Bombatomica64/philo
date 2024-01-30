/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:42:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/30 12:54:03 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork_and_print(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork[id]);
	print_action(data, FORK, id, ft_get_time(&data->time));
}

void	unlock_fork_and_print(t_data *data, int id)
{
	pthread_mutex_unlock(&data->fork[id]);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
}

void	handle_last_philosopher(t_data *data, int id, t_bool *both)
{
	pthread_mutex_lock(&data->fork[0]);
	print_action(data, FORK, id, ft_get_time(&data->time));
	get_food(data, id);
	unlock_fork_and_print(data, 0);
	*both = TRUE;
	unlock_fork_and_print(data, id);
	think_and_die(data, id, *both);
}

void	handle_other_philosophers(t_data *data, int id, t_bool *both)
{
	pthread_mutex_lock(&data->fork[id + 1]);
	print_action(data, FORK, id, ft_get_time(&data->time));
	get_food(data, id);
	unlock_fork_and_print(data, id + 1);
	*both = TRUE;
	unlock_fork_and_print(data, id);
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
	odd_wait(id);
	while (data->thrds[id].philo->go_on == TRUE)
	{
		both = FALSE;
		lock_fork_and_print(data, id);
		if (id == data->nb_fork - 1)
			handle_last_philosopher(data, id, &both);
		else if (id != data->nb_fork - 1)
			handle_other_philosophers(data, id, &both);
	}
	return (NULL);
}
