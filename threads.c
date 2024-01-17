/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/17 17:29:12 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_threads(t_data *data)
{
	int		i;

	i = 0;
	data->thrds = malloc(sizeof(t_thread) * data->nb_philo);
	gettimeofday(&data->time.start, NULL);
	while (i < data->nb_philo)
	{
		data->thrds->philo->id = i;
		data->thrds[i].philo->left_to_eat = data->nb_eat;
		data->thrds[i].philo->life.start = data->time.start;
		pthread_mutex_init(data->thrds[i].philo->forks, NULL);
		pthread_create(&data->thrds[i].thread, NULL, &routine, &data->thrds[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->thrds[i].thread, NULL);
		i++;
	}
}
