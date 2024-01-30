/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:18:01 by mruggier          #+#    #+#             */
/*   Updated: 2024/01/30 17:41:25 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_food(t_data *data, int id)
{
	if (go_on_change(data, FALSE) == FALSE)
		return (0);
	print_action(data, EAT, id, ft_get_time(&data->time, data));
	get_start(&data->thrds[id].philo->life_left, data);
	ft_msleep(data->time_to_eat);
	if (go_on_change(data, FALSE) == FALSE)
		return (0);
	check_food(data, id, 1);
	return (1);
}

void	think_and_die(t_data *data, int id, t_bool both)
{
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time, data));
	if (both == TRUE)
	{
		print_action(data, SLEEP, id, ft_get_time(&data->time, data));
		ft_msleep(data->time_to_sleep);
		print_action(data, THINK, id, ft_get_time(&data->time, data));
	}
}
