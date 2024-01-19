/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/19 13:00:00 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_data *data, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_action(data, FORK, data->thrds->philo->id, ft_get_time(data->time.start));
	return (1);
}

int	giveup_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
	return (-1);
}

void	*routine(void *d)
{
	t_bool	go_on;
	t_data_id	*all;
	t_data	*data; 
	
	all = (t_data_id *)d;
	data = all->data;
	if (data->start == TRUE && data->thrds->philo->id % 2 != 0)
		usleep(100);
	go_on = TRUE;
	while(go_on == TRUE)
	{
		data->thrds[all->id].philo->n_fork += get_fork(data, data->thrds[all->id].philo->fork);
		if (all->id == data->nb_philo - 1)
			data->thrds[all->id].philo->n_fork += get_fork(data, data->thrds[0].philo->fork);
		else
			data->thrds[all->id].philo->n_fork += get_fork(data, data->thrds[all->id + 1].philo->fork);

		if (data->thrds[all->id].philo->n_fork == 2)
			get_food(data, all->id);

		data->thrds[all->id].philo->n_fork += giveup_fork(data);
		if (all->id == data->nb_philo - 1)
			data->thrds[all->id].philo->n_fork += giveup_fork(data->thrds[0].philo->fork);
		else
			data->thrds[all->id].philo->n_fork += giveup_fork(data->thrds[all->id + 1].philo->fork);
		if (data->thrds->philo->left_to_eat == 0)
			go_on = FALSE;
	}
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
		data->thrds[i].philo->id = i;
		data->thrds[i].philo->left_to_eat = data->nb_eat;
		data->thrds[i].philo->life.start = data->time.start;
		pthread_mutex_init(data->thrds[i].philo->fork, NULL);
		pthread_create(&data->thrds[i].thread, NULL, &routine, get_data_id(data, i));});
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->thrds[i].thread, NULL);
		i++;
	}
}
