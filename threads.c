/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/27 17:36:09 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_bool	go_on_change(t_data *data, t_bool action)
{
	t_bool	tmp;

	pthread_mutex_lock(&data->go_on_mutex);
	if (action == TRUE)
	{
		data->go_on = FALSE;
		philo_stop(data);
		pthread_mutex_unlock(&data->go_on_mutex);
		return (FALSE);
	}
	else if (action == ERROR)
	{
		pthread_mutex_unlock(&data->go_on_mutex);
		pthread_mutex_destroy(&data->go_on_mutex);
		return (FALSE);
	}
	else if (action == FALSE)
	{
		tmp = data->go_on;
		pthread_mutex_unlock(&data->go_on_mutex);
		return (tmp);
	}
	return (ERROR);
}

void	number_of_times_eaten(t_data *data, int id, t_bool eat)
{
	int	i;

	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->eating = FALSE;
	if (eat == TRUE)
	{
		data->thrds[id].philo->left_to_eat--;
		pthread_mutex_unlock(&data->nb_eaten_mutex);
		data->eating = TRUE;
		return ;
	}
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
			go_on_change(data, TRUE);
		}
	}
	pthread_mutex_unlock(&data->nb_eaten_mutex);
	data->eating = TRUE;
}
// crea un check_life per nb_time eaten, e crea una funzione check_food(t_data *data, int id, int add);
// che incrementa il numero di volte che ha mangiato il filosofo e controlla se ha mangiato abbastanza volte
// TODO number_of_times_eaten quindi va spostata. per risolvere deadlock. mutex dentro un altro mutex
int	get_food(t_data *data, int id)
{
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);
	ft_msleep(data->time_to_eat);
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	number_of_times_eaten(data, id, TRUE);
	number_of_times_eaten(data, id, FALSE);
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
		ft_msleep(100);
	while (data->thrds[id].philo->go_on == TRUE)
	{
		both = FALSE;
		pthread_mutex_lock(&data->fork[id]);
		data->thrds[id].philo->fork_av = FALSE;
		print_action(data, FORK, id, ft_get_time(&data->time));
		if (id == data->nb_fork - 1)
		{
			pthread_mutex_lock(&data->fork[0]);
			data->thrds[0].philo->fork_av = FALSE;
			print_action(data, FORK, id, ft_get_time(&data->time));
			
			
			get_food(data, id);
			
			
			pthread_mutex_unlock(&data->fork[0]);
			data->thrds[0].philo->fork_av = TRUE;
			print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
			both = TRUE;
			pthread_mutex_unlock(&data->fork[id]);
			data->thrds[id].philo->fork_av = TRUE;
			think_and_die(data, id, both);
		}
		else if (id != data->nb_fork - 1)
		{
			pthread_mutex_lock(&data->fork[id + 1]);
			data->thrds[id + 1].philo->fork_av = FALSE;
			print_action(data, FORK, id, ft_get_time(&data->time));
			
			
			get_food(data, id);
			
			
			print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
			both = TRUE;
			pthread_mutex_unlock(&data->fork[id + 1]);
			data->thrds[id + 1].philo->fork_av = TRUE;
			pthread_mutex_unlock(&data->fork[id]);
			data->thrds[id].philo->fork_av = TRUE;
			think_and_die(data, id, both);
		}
	}
	pthread_mutex_destroy(&data->fork[id]);
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
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_fork);
	data->nb_fed = 0;
	pthread_mutex_init(&data->nb_eaten_mutex, NULL);
	while (i < data->nb_philo)
	{
		data->thrds[i].philo = malloc(sizeof(t_philo));
		data->thrds[i].thread = malloc(sizeof(pthread_t));
		data->thrds[i].philo->id = i;
		data->thrds[i].philo->left_to_eat = data->nb_eat;
		get_start(&data->thrds[i].philo->life_left);
		data->thrds[i].philo->n_fork = 0;
		data->thrds[i].philo->start = TRUE;
		data->thrds[i].philo->go_on = TRUE;
		//data->thrds[i].philo->fork_av = TRUE;
		data->thrds[i].philo->overfed = FALSE;
		data_id = get_data_id(data, i);
		//data->nb_times_eaten = data->nb_eat * data->nb_philo;
		//printf("data->nb_times_eaten[%d]\n", data->nb_times_eaten);
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_lock(&data->fork[i]);
		data->thrds[i].philo->fork_av = FALSE;
		pthread_create(data->thrds[i].thread, NULL,
			&routine, data_id);
		//free(data_id);
		pthread_detach(*data->thrds[i].thread);
		i++;
	}
	i = 0;
	while (i < data->nb_fork)
	{
		pthread_mutex_unlock(&data->fork[i]);
		data->thrds[i].philo->fork_av = TRUE;
		i++;
	}
	data->thread_alive = malloc(sizeof(pthread_t));
	pthread_create(data->thread_alive, NULL, &check_life, data);
	join_philo(data);
	pthread_detach(*data->thread_alive);
	while (TRUE)
		if (go_on_change(data, FALSE) == FALSE)
		{
			data->nb_fed = data->nb_fork;
			printf("fine\n");
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