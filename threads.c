/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/25 12:54:27 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	get_food(t_data *data, int id)
{
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);

/*
	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->thrds[id].philo->left_to_eat--;
	pthread_mutex_unlock(&data->nb_eaten_mutex);
*/

	ft_msleep(data->time_to_eat);
	data->thrds[id].philo->left_to_eat--;
	//printf("\033[31mlte[%d]\033[0m\n", data->thrds[id].philo->left_to_eat);
	return (1);
}

void	think_and_die(t_data *data, int id, t_bool both)
{
	pthread_mutex_unlock(data->thrds[id].philo->fork);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	if (both == TRUE)
	{
		print_action(data, SLEEP, id, ft_get_time(&data->time));
		ft_msleep(data->time_to_sleep);
		print_action(data, THINK, id, ft_get_time(&data->time));
	}
}
		/* fork_acquiring(data, id);
		if (data->thrds[id].philo->n_fork == 2)
			get_food(data, id);
		fork_releasing(data, id);
		think_and_die(data, id);
		if (data->thrds->philo->left_to_eat == 0)
			data->thrds[id].philo->go_on = FALSE; */

void	*routine(void *d)
{
	t_data		*data;
	t_data_id	*all;
	int			id;

	all = (t_data_id *)d;
	id = all->id;
	data = all->data;
	// free(d);
	free(all);
	ft_msleep(100);
	//printf("id[%d]\n", all->id % 2);
	if (data->thrds[id].philo->start == TRUE && id % 2 != 0)
	{
		ft_msleep(10); ///////non cambia nulla se cambio il valore
		//printf("sveglia dispari%d\n", id);
	}
	data->thrds[id].philo->start = FALSE;
	while (data->thrds[id].philo->go_on == TRUE)
	{
		if (pthread_mutex_lock(data->thrds[id].philo->fork) == 0)
		{
			print_action(data, FORK, id, ft_get_time(&data->time));
			if (id == data->nb_fork - 1)
			{	
				if (pthread_mutex_lock(data->thrds[0].philo->fork) == 0)
				{
					print_action(data, FORK, id, ft_get_time(&data->time));
					get_food(data, id);
					pthread_mutex_unlock(data->thrds[0].philo->fork);
					print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
					think_and_die(data, id, TRUE);
				}
			}
			else
			{
				if (pthread_mutex_lock(data->thrds[id + 1].philo->fork) == 0)
				{
					print_action(data, FORK, id, ft_get_time(&data->time));
					get_food(data, id);
					pthread_mutex_unlock(data->thrds[id + 1].philo->fork);
					print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
					think_and_die(data, id, TRUE);
				}
				think_and_die(data, id, FALSE);
			}
		}
	}
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
	int			i;
	t_data_id	*data_id;

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
		data->thrds[i].philo->fork_av = TRUE;
		data_id = get_data_id(data, i);
		pthread_mutex_init(data->thrds[i].philo->fork, NULL);
		
		
	//	printf("data->nb_eat[%d]\n", data->nb_eat);
		/*
		pthread_mutex_init(&data->nb_eaten_mutex, NULL);
		data->nb_times_eaten = data->nb_eat * data->nb_philo;
		*/
		
		pthread_create(data->thrds[i].thread, NULL,
			&routine, data_id);
		//free(data_id);
		pthread_detach(*data->thrds[i].thread);
		i++;
	}
	data->thread_alive = malloc(sizeof(pthread_t));
	pthread_create(data->thread_alive, NULL, &check_life, data);
	pthread_detach(*data->thread_alive);
	join_philo(data);
	while (TRUE)
		if (data->go_on == FALSE)
		{
			printf("fine\n");
			ft_close(data);
		}
}

void	join_philo(t_data *data)
{
	// int	j;

	// j = 0;
	pthread_join(*data->thread_alive, NULL);
	/*if (data->nb_fork == 1)
			return ;*/
	/*while (j < data->nb_fork)
	{
		pthread_join(*data->thrds[j].thread, NULL);
		printf("qualvghvghcosa\n");
		j++;
	}*/
}
