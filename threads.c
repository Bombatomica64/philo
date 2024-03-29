/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 18:36:21 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	initialize_philosopher(t_data *data, int i)
{
	data->thrds[i].philo = malloc(sizeof(t_philo));
	data->thrds[i].thread = malloc(sizeof(pthread_t));
	data->thrds[i].philo->id = i;
	data->thrds[i].philo->left_to_eat = data->nb_eat;
	get_start(&data->thrds[i].philo->life_left, data);
	data->thrds[i].philo->n_fork = 0;
	data->thrds[i].philo->start = TRUE;
	data->thrds[i].philo->go_on = TRUE;
	data->thrds[i].philo->overfed = FALSE;
	pthread_mutex_init(&data->fork_mutex, NULL);
}

void	create_philosopher_thread(t_data *data, int i)
{
	t_data_id	*data_id;

	data_id = get_data_id(data, i);
	pthread_create(data->thrds[i].thread, NULL, &routine, data_id);
}

void	unlock_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_fork)
	{
		pthread_mutex_unlock(&data->fork[i]);
		i++;
	}
}

void	make_threads(t_data *data)
{
	int	i;

	i = 0;
	data->thrds = malloc(sizeof(t_thread) * data->nb_philo);
	get_start(&data->time, data);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_fork);
	data->nb_fed = 0;
	pthread_mutex_init(&data->nb_eaten_mutex, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		initialize_philosopher(data, i++);
	}
	i = 0;
	while (i < data->nb_philo)
		create_philosopher_thread(data, i++);
	data->thread_alive = malloc(sizeof(pthread_t));
	pthread_create(data->thread_alive, NULL, &check_life, data);
	join_philo(data);
	pthread_detach(*data->thread_alive);
	while (TRUE)
	{
		if (go_on_change(data, FALSE) == FALSE)
			ft_close(data);
	}
}

void	join_philo(t_data *data)
{
	pthread_join(*data->thread_alive, NULL);
}
	/*if (data->nb_fork == 1)
			return ;*/
	/*while (j < data->nb_fork)
	{
		pthread_join(*data->thrds[j].thread, NULL);
		printf("qualvghvghcosa\n");
		j++;
	}*/