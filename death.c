/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:34:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/27 16:26:50 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	printf("nb_fed[%d]\n", data->nb_fed);
	ft_msleep(data->time_to_eat + 10);
	while (i < data->nb_fork)
	{
		free(data->thrds[i].thread);
		free(data->thrds[i].philo);
		i++;
	}
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

void	*check_life(void *da)
{
	t_data		*data;
	int			j;

	data = (t_data *)da;
	j = data->nb_fork;
	while (j != -1 && go_on_change(data, FALSE) == TRUE)
	{
		j = 0;
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