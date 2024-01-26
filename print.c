/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/25 17:44:34 by mruggier         ###   ########.fr       */
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
		usleep(10);
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
	//printf("data->thrds[%d].philo->go_on[%d]\n", id, data->thrds[id].philo->go_on);
	pthread_mutex_lock(data->print);
	if (data->go_on == FALSE)
	{
		//pthread_mutex_unlock(data->print);
		return ;
	}
	data->print_av = FALSE;
	if (action == EAT)
		printf("\033[1m%ld\033[0;91m philo[%d] is eating\033[0m 🍝️\n", time_since, id);
	else if (action == SLEEP)
		printf("\033[1m%ld \033[0;34mphilo[%d] is sleeping\033[0m 😴️\n", time_since, id);
	else if (action == THINK)
		printf("\033[1m%ld \033[0;36mphilo[%d] is thinking\033[0m 🤔️\n", time_since, id);
	else if (action == DIED)
		printf("\033[31m%ld \033[0;31mphilo[%d] died \033[0m 💀️\n", time_since, id);
	else if (action == FORK)
		printf("\033[1m%ld \033[0;93mphilo[%d] has taken a fork\033[0m 🔱️\n", time_since, id);
	else if (action == FORK_LEFT)
		printf("\033[1m%ld\033[0;35m philo[%d] has left a fork\033[0m\n", time_since, id);
	else if (action == FED)
		printf("\033[32m%ld Each philo ate %i times and it's full\033[0m\n",
			time_since, data->nb_eat);
	pthread_mutex_unlock(data->print);
	data->print_av = TRUE;
}
