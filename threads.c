/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/23 16:18:14 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	get_food(t_data *data, int id)
{
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);
	ft_msleep(data->time_to_eat);
	data->thrds[id].philo->left_to_eat--;
	return (1);
}

/*void	think_and_die(t_data *data, t_data_id *all)
{
	int		i;

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
	}
	while (data->go_on == TRUE)
	{
		if (data->thrds[all->id].philo->life_left.time_since <= 0)
		{
			print_action(data, DIED, all->id, ft_get_time(&data->time));
			data->go_on = FALSE;
			return ;
		}
		else
		{
			printf("ciao id[%d]\n", all->id);
		}
		print_action(data, THINK, all->id,
			ft_get_time(&data->time));
		usleep(data->time_to_sleep);
		data->thrds[all->id].philo->life_left.time_since -= data->time_to_sleep;
	}
}*/

void	*routine(void *d)
{
	t_data		*data;
	t_data_id	*all;
	int			id;

	all = (t_data_id *)d;
	id = all->id;
	data = all->data;
	free(all);
	//printf("id[%d]\n", all->id % 2);
	if (data->thrds[id].philo->start == TRUE && id % 2 != 0)
	{
		ft_msleep(100); ///////non cambia nulla se cambio il valore
	}
	data->thrds[id].philo->start = FALSE;
	while (data->thrds[id].philo->go_on == TRUE)
	{
		fork_acquiring(data, id);
		if (data->thrds[id].philo->n_fork == 2)
			get_food(data, id);
		//think_and_die(data, all);
		fork_releasing(data, id);
		if (data->thrds->philo->left_to_eat == 0)
			data->thrds[id].philo->go_on = FALSE;
	}
	data->nb_philo--;
	//think_and_die(data, all);
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
	get_start(&data->time);
	while (i < data->nb_philo)
	{
		data->thrds[i].philo = malloc(sizeof(t_philo));
		data->thrds[i].philo->fork = malloc(sizeof(pthread_mutex_t));
		data->thrds[i].thread = malloc(sizeof(pthread_t));
		data->thrds[i].philo->id = i;
		data->thrds[i].philo->left_to_eat = data->nb_eat;
		get_start(&data->thrds[i].philo->life_left);
		data->thrds[i].philo->n_fork = 0;
		data->thrds[i].philo->start = TRUE;
		data->thrds[i].philo->go_on = TRUE;
		pthread_mutex_init(data->thrds[i].philo->fork, NULL);
		pthread_create(data->thrds[i].thread, NULL,
			&routine, get_data_id(data, i));
		i++;
	}
	data->thread_alive = malloc(sizeof(pthread_t));
	printf("nb_fork[%d]\n", data->nb_fork);
	pthread_create(data->thread_alive, NULL, &check_life, data);
	join_philo(data);
	ft_close(data);
}

void	join_philo(t_data *data)
{
	int j;

	j = 0;
	while (j < data->nb_philo)
	{
		if (j == 0)
			pthread_join(*data->thread_alive, NULL);
		pthread_join(*data->thrds[j].thread, NULL);
		j++;
	}
}
