/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:34:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/23 16:30:51 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_fork)
	{
		pthread_mutex_destroy(data->thrds[i].philo->fork);
		free(data->thrds[i].philo->fork);
		free(data->thrds[i].philo);
		pthread_detach(*data->thrds[i].thread);
		free(data->thrds[i].thread);
		i++;
	}
	pthread_detach(*data->thread_alive);
	free(data->thread_alive);
	free(data->thrds);
	if (data->print)
	{
		pthread_mutex_destroy(data->print);
		free(data->print);
	}
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

void	*check_life(void *da)
{
	t_data		*data;
	int			j;

	//i = 0;
	data = (t_data *)da;
	j = data->nb_fork;
	while (j != -1)
	{
		//printf("\033[32m nb_philo = %d\033[0m\n", data->nb_fork);
		j = 0;
		while (j < data->nb_fork)
		{
			data->thrds[j].philo->life_left.time_since = ft_get_time(
					&data->thrds[j].philo->life_left);
			if (data->thrds[j].philo->life_left.time_since > data->time_to_die)
			{
				printf("time_since[%ld]\n", data->thrds[j].philo->life_left.time_since);
				print_action(data, DIED, j, ft_get_time(&data->time));
				philo_stop(data);
				data->go_on = FALSE;
				return (NULL);
			}
			//printf("\033[32mj = %d\033[0m\n", j);
			j++;
		}
	}
	return (NULL);
}

				// data->thrds[j].philo->go_on = FALSE;