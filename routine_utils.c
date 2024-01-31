/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:30:03 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 18:07:57 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd_wait(int id, t_data *data)
{
	(void)data;
	if (id % 2 != 0)
		ft_msleep(data->time_to_eat - 5);
}

void	*highlander(t_data *data, int id)
{
	if (data->nb_fork == 1)
	{
		print_action(data, FORK, id, ft_get_time(&data->time, data));
		ft_msleep(data->time_to_die + 5);
		return (NULL);
	}
	return (NULL);
}
