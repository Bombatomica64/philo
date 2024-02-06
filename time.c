/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:28:40 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/06 11:46:56 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_current_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	ft_msleep(int time)
{
	long long	tmp;

	tmp = ft_current_time() + time;
	while (ft_current_time() < tmp)
		usleep(250);
}

void	get_start(t_time *start, t_data *data)
{
	pthread_mutex_lock(&data->time_mutex);
	gettimeofday(&start->start, NULL);
	start->start_ms = (start->start.tv_sec) * 1000
		+ (start->start.tv_usec) / 1000;
	pthread_mutex_unlock(&data->time_mutex);
}

long	ft_get_time(t_time *start, t_data *data)
{
	long			time_since;

	pthread_mutex_lock(&data->time_mutex);
	time_since = ft_current_time() - start->start_ms;
	pthread_mutex_unlock(&data->time_mutex);
	return (time_since);
}
