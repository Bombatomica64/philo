/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:18:01 by mruggier          #+#    #+#             */
/*   Updated: 2024/01/22 17:07:38 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_releasing(t_data *data, t_data_id *all)
{
	data->thrds[all->id].philo->n_fork
		+= giveup_fork(&data->thrds[all->id].philo->fork);
	if (all->id == data->nb_philo - 1)
		data->thrds[all->id].philo->n_fork
			+= giveup_fork(&data->thrds[0].philo->fork);
	else
		data->thrds[all->id].philo->n_fork
			+= giveup_fork(&data->thrds[all->id + 1].philo->fork);
}

void	fork_acquiring(t_data *data, t_data_id *all)
{
	data->thrds[all->id].philo->n_fork
		+= get_fork(data, &data->thrds[all->id].philo->fork, all->id);
	if (all->id == data->nb_philo - 1)
		data->thrds[all->id].philo->n_fork
			+= get_fork(data, &data->thrds[0].philo->fork, all->id);
	else
		data->thrds[all->id].philo->n_fork
			+= get_fork(data, &data->thrds[all->id + 1].philo->fork, all->id);
}

int	get_fork(t_data *data, pthread_mutex_t *fork, int id)
{
	pthread_mutex_lock(fork);
	print_action(data, FORK, id, ft_get_time(&data->time.start));
	return (1);
}

int	giveup_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
	return (-1);
}
