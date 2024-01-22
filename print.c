/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 18:25:23 by lmicheli         ###   ########.fr       */
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
		usleep(100);
}

void	get_start(t_time *start)
{
	gettimeofday(&start->start, NULL);
	start->start_ms = (start->start.tv_sec) * 1000
		+ (start->start.tv_usec) / 1000;
}

long	ft_get_time(t_time *start)
{
	long			time_since;

	time_since = ft_current_time() - start->start_ms;
	return (time_since);
}

/* long	ft_get_time(struct timeval start)
{
	struct timeval	now;
	long			time_since;

	gettimeofday(&now, NULL);
	time_since = (now.tv_sec - start.tv_sec) * 1000;
	time_since += (now.tv_usec - start.tv_usec);
	printf("time_since[%ld]\n", time_since);
	return (time_since);
} */

void	print_action(t_data *data, t_action action, int id, long time_since)
{
	pthread_mutex_lock(data->print);
	if (action == EAT)
		printf("%ld philo[%d] is eating\n", time_since, id);
	else if (action == SLEEP)
		printf("%ld philo[%d] is sleeping\n", time_since, id);
	else if (action == THINK)
		printf("%ld philo[%d] is thinking\n", time_since, id);
	else if (action == DIED)
		printf("%ld philo[%d] died\n", time_since, id);
	else if (action == FORK)
		printf("%ld philo[%d] has taken a fork\n", time_since, id);
	else if (action == FORK_LEFT)
		printf("%ld philo[%d] has left a fork\n", time_since, id);
	pthread_mutex_unlock(data->print);
}
