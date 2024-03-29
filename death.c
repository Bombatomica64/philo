/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:34:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 10:31:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			print_action(data, FED, id, ft_get_time(&data->time, data));
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
					&data->thrds[j].philo->life_left, data);
			if (data->thrds[j].philo->life_left.time_since > data->time_to_die)
			{
				go_on_change(data, TRUE);
				print_action(data, DIED, j, ft_get_time(&data->time, data));
				return (NULL);
			}
			j++;
		}
	}
	return (NULL);
}

				// data->thrds[j].philo->go_on = FALSE;