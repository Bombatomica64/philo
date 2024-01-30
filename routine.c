/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:42:56 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/30 11:43:14 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_food(t_data *data, int id)
{
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);
	ft_msleep(data->time_to_eat);
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	check_food(data, id, 1);
	return (1);
}

void	think_and_die(t_data *data, int id, t_bool both)
{
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	if (both == TRUE)
	{
		print_action(data, SLEEP, id, ft_get_time(&data->time));
		ft_msleep(data->time_to_sleep);
		print_action(data, THINK, id, ft_get_time(&data->time));
	}
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
	{
		print_action(data, FORK, id, ft_get_time(&data->time));
		ft_msleep(data->time_to_die + 5);
		return (NULL);
	}
	if (data->thrds[id].philo->start == TRUE && id % 2 != 0)
		ft_msleep(1);
	while (data->thrds[id].philo->go_on == TRUE)
	{
		both = FALSE;
		pthread_mutex_lock(&data->fork[id]);
		data->thrds[id].philo->fork_av = FALSE;
		print_action(data, FORK, id, ft_get_time(&data->time));
		if (id == data->nb_fork - 1)
		{
			pthread_mutex_lock(&data->fork[0]);
			print_action(data, FORK, id, ft_get_time(&data->time));
			get_food(data, id);
			pthread_mutex_unlock(&data->fork[0]);
			print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
			both = TRUE;
			pthread_mutex_unlock(&data->fork[id]);
			think_and_die(data, id, both);
		}
		else if (id != data->nb_fork - 1)
		{
			pthread_mutex_lock(&data->fork[id + 1]);
			print_action(data, FORK, id, ft_get_time(&data->time));
			get_food(data, id);
			print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
			both = TRUE;
			pthread_mutex_unlock(&data->fork[id + 1]);
			pthread_mutex_unlock(&data->fork[id]);
			think_and_die(data, id, both);
		}
	}
	return (NULL);
}