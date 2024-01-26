/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/26 11:39:23 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	number_of_times_eaten(t_data *data, int id)
{
	int	i;

	pthread_mutex_lock(&data->nb_eaten_mutex);
	if (data->thrds[id].philo->left_to_eat == 0)
	{
		data->thrds[id].philo->overfed = TRUE;
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->thrds[i].philo->left_to_eat == 0)
				i++;
			else
				break ;
		}
		if (i == data->nb_philo)
		{
			print_action(data, FED, id, ft_get_time(&data->time));
			data->go_on = FALSE;
		}
	}
	pthread_mutex_unlock(&data->nb_eaten_mutex);
}

int	get_food(t_data *data, int id)
{
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);
	ft_msleep(data->time_to_eat);
	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->thrds[id].philo->left_to_eat--;
	pthread_mutex_unlock(&data->nb_eaten_mutex);
	number_of_times_eaten(data, id);
	return (1);
}

/*
	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->nb_times_eaten--;
	printf("data->nb_times_eaten[%d]\n", data->nb_times_eaten);
	pthread_mutex_unlock(&data->nb_eaten_mutex);
*/
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
	/*
	if(both == FALSE)
	{
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	
		pthread_mutex_unlock(data->thrds[id].philo->fork);
		return ;
	}
	//print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	if (id == data->nb_fork - 1)
	{
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	
		pthread_mutex_unlock(data->thrds[0].philo->fork);
	}
	else
	{
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
		pthread_mutex_unlock(data->thrds[id + 1].philo->fork);
	}
	if (both == TRUE)
	{
		print_action(data, SLEEP, id, ft_get_time(&data->time));
		ft_msleep(data->time_to_sleep);
		print_action(data, THINK, id, ft_get_time(&data->time));
	}*/

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
	free(all);
	ft_msleep(1);
	if (data->thrds[id].philo->start == TRUE && id % 2 != 0)
	{
		ft_msleep(100);
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
			else if (id != data->nb_fork - 1)
			{
				if (pthread_mutex_lock(data->thrds[id + 1].philo->fork) == 0)
				{
					print_action(data, FORK, id, ft_get_time(&data->time));
					get_food(data, id);
					pthread_mutex_unlock(data->thrds[id + 1].philo->fork);
					print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
					think_and_die(data, id, TRUE);
				}
			}
			think_and_die(data, id, FALSE);
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
		data->thrds[i].philo->overfed = FALSE;
		data_id = get_data_id(data, i);
		pthread_mutex_init(data->thrds[i].philo->fork, NULL);
		
		
		
		pthread_mutex_init(&data->nb_eaten_mutex, NULL);
		//data->nb_times_eaten = data->nb_eat * data->nb_philo;
		//printf("data->nb_times_eaten[%d]\n", data->nb_times_eaten);
		pthread_create(data->thrds[i].thread, NULL,
			&routine, data_id);
		//free(data_id);
		pthread_detach(*data->thrds[i].thread);
		i++;
	}
	data->thread_alive = malloc(sizeof(pthread_t));
	pthread_create(data->thread_alive, NULL, &check_life, data);
	join_philo(data);
	pthread_detach(*data->thread_alive);
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
