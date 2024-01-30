/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:34:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/30 15:23:03 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/* 
void	destroy_mutexes(t_data *data, int num, t_bool destroy)
{
	int		i;

	pthread_mutex_lock(&data->end);
	i = 0;
	if (destroy == TRUE)
	{
		printf("here\n");
		while (i < num)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
	}
	else
	{
		if (destroy == FALSE)
		{
			printf("destroy_mutexes\n num = %d\n", num);
			pthread_mutex_lock(&data->fork[num]);
			pthread_mutex_unlock(&data->end);
			return ;
		}
		else
		{
			pthread_mutex_unlock(&data->fork[num]);
			pthread_mutex_unlock(&data->end);
			return ;
		}
	}
} */

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_fork)
	{
		pthread_join(*data->thrds[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_fork)
	{
		pthread_mutex_destroy(&data->fork[i]);
		free(data->thrds[i].thread);
		free(data->thrds[i].philo);
		i++;
	}
	go_on_change(data, ERROR);
	pthread_mutex_destroy(&data->go_on_mutex);
	pthread_mutex_destroy(&data->nb_eaten_mutex);
	pthread_mutex_destroy(&data->print);


	pthread_mutex_destroy(&data->mutex);

	
	free(data->fork);
	free(data->thread_alive);
	free(data->thrds);
	free(data);
	exit(EXIT_FAILURE);
}

void	philo_stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_fork)
	{
		data->thrds[i].philo->go_on = FALSE;
		i++;
	}
}

void	check_food(t_data *data, int id, int add)
{
	int		i;
	int		nb_fed;

	i = 0;
	nb_fed = 0;
	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->thrds[id].philo->left_to_eat -= add;
	if (data->thrds[id].philo->left_to_eat == 0)
	{
		data->thrds[id].philo->overfed = TRUE;
		while (i < data->nb_philo)
		{
			if (data->thrds[i].philo->overfed == TRUE)
				nb_fed++;
			i++;
		}
		if (nb_fed == data->nb_philo)
		{
			print_action(data, FED, id, ft_get_time(&data->time));
			go_on_change(data, TRUE);
		}
	}
	pthread_mutex_unlock(&data->nb_eaten_mutex);
}

void	*check_life(void *da)
{
	t_data		*data;
	int			j;

	data = (t_data *)da;
	j = data->nb_fork;
	while (j != -1 && go_on_change(data, FALSE) == TRUE)
	{
		j = 0;
		check_food(data, j, 0);
		while (j < data->nb_fork)
		{
			data->thrds[j].philo->life_left.time_since = ft_get_time(
					&data->thrds[j].philo->life_left);
			if (data->thrds[j].philo->life_left.time_since > data->time_to_die)
			{
				go_on_change(data, TRUE);
				print_action(data, DIED, j, ft_get_time(&data->time));
				return (NULL);
			}
			j++;
		}
	}
	return (NULL);
}

				// data->thrds[j].philo->go_on = FALSE;