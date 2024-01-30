/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:30:03 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/30 12:33:23 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	odd_wait(int id)
{
	if (id % 2 != 0)
		ft_msleep(1);
}

void	*highlander(t_data *data, int id)
{
	if (data->nb_fork == 1)
	{
		print_action(data, FORK, id, ft_get_time(&data->time));
		ft_msleep(data->time_to_die + 5);
		return (NULL);
	}
	return (NULL);
}
