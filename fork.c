/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:18:01 by mruggier          #+#    #+#             */
/*   Updated: 2024/01/30 12:33:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_food(t_data *data, int id)
{
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	print_action(data, EAT, id, ft_get_time(&data->time));
	get_start(&data->thrds[id].philo->life_left);
	ft_msleep(data->time_to_eat);
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	check_food(data, id, 1);
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
