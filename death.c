/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:34:48 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 12:51:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_close(t_data *data)
{
	int	i;

	i = 0;
	(void)data;
	exit(0);
	while (i < data->nb_fork)
	{
		pthread_mutex_destroy(&data->thrds[i].philo->fork);
		free(data->thrds[i].philo);
		free(data->thrds[i].thread);
		i++;
	}
	free(data->thrds);
	if (data->print)
	{
		pthread_mutex_destroy(data->print);
		free(data->print);
	}
	free(data);
}

void	*check_life(void *da)
{
	t_data		*data;
	int			i;

	i = 0;
	data = (t_data *)da;
	while (data->go_on == TRUE)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			data->thrds[i].philo->life_left.time_since = ft_get_time(
					data->thrds[i].philo->life_left.start);
			if (data->thrds[i].philo->life_left.time_since <= 0)
			{
				print_action(data, DIED, i, ft_get_time(data->time.start));
				data->go_on = FALSE;
				ft_close(data);
			}
			i++;
		}
	}
	return (NULL);
}
