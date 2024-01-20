/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:58 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/20 11:29:05 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;

	while (i < data->nb_fork)
	{
		mutex_destroy(data, i);
		free_philo(data, i);
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

void	free_philo(t_data *data, int i)
{
	if (data->thrds[i].philo)
		free(data->thrds[i].philo);
}

void	mutex_destroy(t_data *data, int i)
{
	if (data->thrds[i].philo->fork)
		pthread_mutex_destroy(data->thrds[i].philo->fork);
}
