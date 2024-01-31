/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:12:25 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 15:35:16 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	make_processes(t_data_bonus *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
			philo_life(data, i);
		i++;
	}
}
