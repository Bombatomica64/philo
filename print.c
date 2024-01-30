/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:47:59 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/30 16:14:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, t_action action, int id, long time_since)
{
/* 	if (go_on_change(data, FALSE) == FALSE && action != DIED)
	{
		return ;
	} */
	pthread_mutex_lock(&data->print);
	prints(action, time_since, id, data);
	pthread_mutex_unlock(&data->print);
	if (action == DIED)
		pthread_mutex_destroy(&data->print);
}

void	prints(t_action action, long time_since, int id, t_data *data)
{
	if (go_on_change(data, FALSE) == FALSE && action != DIED)
		return ;
	if (action == EAT)
		printf("\033[1m%ld\033[0;91m philo[%d] is eating\033[0m 🍝️\n",
			time_since, id);
	else if (action == SLEEP)
		printf("\033[1m%ld \033[0;34mphilo[%d] is sleeping\033[0m 💤️\n",
			time_since, id);
	else if (action == THINK)
		printf("\033[1m%ld \033[0;36mphilo[%d] is thinking\033[0m 💭️\n",
			time_since, id);
	else if (action == DIED)
		printf("\033[31m%ld \033[0;31mphilo[%d] died \033[0m💀️\n",
			time_since, id);
	else if (action == FORK)
		printf("\033[1m%ld \033[0;93mphilo[%d] has taken a fork\033[0m 🍴️\n",
			time_since, id);
	else if (action == FORK_LEFT)
		printf("\033[1m%ld\033[0;35m philo[%d] has left a fork\033[0m\n",
			time_since, id);
	else if (action == FED)
		printf("\033[32m%ld Each philo ate %i times and it's full\033[0m ⭐️\n",
			time_since, data->nb_eat);
}
