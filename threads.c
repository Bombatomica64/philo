/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 13:03:17 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	get_food(t_data *data, int id)
{
	print_action(data, EAT, id, ft_get_time(data->time.start));
	gettimeofday(&data->thrds[id].philo->life_left.start, NULL);
	usleep(data->time_to_eat);
	data->thrds[id].philo->left_to_eat--;
	
	return (1);
}

void	think_and_die(t_data *data, t_data_id *all)
{
	/*int		i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->thrds[i].philo->left_to_eat == 0)
			i++;
		else
			break;
	}
	if (i == data->nb_philo)
	{
		data->go_on = FALSE;
		return ;
	}*/
	while (data->go_on == TRUE)
	{
		if (data->thrds[all->id].philo->life_left.time_since <= 0)
		{
			print_action(data, DIED, all->id, ft_get_time(data->time.start));
			data->go_on = FALSE;
			return ;
		}
		else
		{
			printf("ciao id[%d]\n", all->id);
		}
		print_action(data, THINK, all->id,
			ft_get_time(data->time.start));
		usleep(data->time_to_sleep);
		data->thrds[all->id].philo->life_left.time_since -= data->time_to_sleep;
	}
}

void	*routine(void *d)
{
	t_data		*data;
	t_data_id	*all;

	all = (t_data_id *)d;
	data = all->data;
	if (data->thrds[all->id].philo->start == TRUE && all->id % 2 != 0)
	{
		usleep(100);
	}
	data->thrds[all->id].philo->start = FALSE;
	while (data->go_on == TRUE)
	{
		fork_acquiring(data, all);
		if (data->thrds[all->id].philo->n_fork == 2)
			get_food(data, all->id);
		//think_and_die(data, all);
		fork_releasing(data, all);
		if (data->thrds->philo->left_to_eat == 0)
			data->go_on = FALSE;
	}
	data->nb_philo--;
	think_and_die(data, all);
	return (NULL);
}

t_data_id	*get_data_id(t_data *data, int id)
{
	t_data_id	*data_id;

	data_id = malloc(sizeof(t_data_id));
	data_id->data = data;
	data_id->id = id;
	return (data_id);
}

void	make_threads(t_data *data)
{
	int		i;

	i = 0;
	data->thrds = malloc(sizeof(t_thread) * data->nb_philo);
	gettimeofday(&data->time.start, NULL);
	while (i < data->nb_philo)
	{
		data->thrds[i].philo = malloc(sizeof(t_philo));
		// data->thrds[i].philo->fork = malloc(sizeof(pthread_mutex_t));
		data->thrds[i].thread = malloc(sizeof(pthread_t));
		data->thrds[i].philo->id = i;
		data->thrds[i].philo->left_to_eat = data->nb_eat;
		gettimeofday(&data->thrds[i].philo->life_left.start, NULL);
		data->thrds[i].philo->n_fork = 0;
		data->thrds[i].philo->start = TRUE;
		pthread_mutex_init(&data->thrds[i].philo->fork, NULL);
		pthread_create(data->thrds[i].thread, NULL,
			&routine, get_data_id(data, i));
		i++;
	}
	data->thread_alive = malloc(sizeof(pthread_t));
	pthread_create(data->thread_alive, NULL, &check_life, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(*data->thrds[i].thread, NULL);
		i++;
	}
	pthread_join(*data->thread_alive, NULL);
}
