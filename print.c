/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 13:02:28 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_get_time(struct timeval start)
{
	struct timeval	now;
	long			time_since;

	gettimeofday(&now, NULL);
	time_since = (now.tv_sec - start.tv_sec) * 1000;
	time_since += (now.tv_usec - start.tv_usec) / 1000;
	printf("time_since[%ld]\n", time_since);
	return (time_since);
}

void	print_action(t_data *data, t_action action, int id, int time_since)
{
	pthread_mutex_lock(data->print);
	if (action == EAT)
		printf("%d philo[%d] is eating\n", time_since, id);
	else if (action == SLEEP)
		printf("%d philo[%d] is sleeping\n", time_since, id);
	else if (action == THINK)
		printf("%d philo[%d] is thinking\n", time_since, id);
	else if (action == DIED)
		printf("%d philo[%d] died\n", time_since, id);
	else if (action == FORK)
		printf("%d philo[%d] has taken a fork\n", time_since, id);
	pthread_mutex_unlock(data->print);
}
