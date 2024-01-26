/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:58 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/26 15:48:12 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_fork)
	{
		mutex_destroy(data, i);
		free_philo(data, i);
		free(data->thrds[i].thread);
		i++;
	}
	free(data->thrds);
	//if (data->print)
	//{
		pthread_mutex_destroy(&data->print);
		//free(data->print);
	//}
	free(data);
}

void	free_philo(t_data *data, int i)
{
	if (data->thrds[i].philo)
		free(data->thrds[i].philo);
}

void	mutex_destroy(t_data *data, int i)
{
	pthread_mutex_destroy(&data->thrds[i].philo->fork);
}
