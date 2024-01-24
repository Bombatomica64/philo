/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:18:01 by mruggier          #+#    #+#             */
/*   Updated: 2024/01/24 16:48:04 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_releasing(t_data *data, int id)
{
	if (data->thrds[id].philo->go_on == FALSE)
		return ;
	data->thrds[id].philo->n_fork
		+= giveup_fork(data->thrds[id].philo->fork, data, id);
	// printf("\033[36mid[%d]\033[0m\n", id);
	if (id == data->nb_fork - 1)
		data->thrds[id].philo->n_fork
			+= giveup_fork(data->thrds[0].philo->fork, data, id);
	else
	{
		data->thrds[id].philo->n_fork
			+= giveup_fork(data->thrds[id + 1].philo->fork, data, id);
	}
}

void	fork_acquiring(t_data *data, int id)
{
	if (data->thrds[id].philo->go_on == FALSE)
		return ;
	data->thrds[id].philo->n_fork
		+= get_fork(data, data->thrds[id].philo->fork, id);
	if (id == data->nb_fork - 1)
		data->thrds[id].philo->n_fork
			+= get_fork(data, data->thrds[0].philo->fork, id);
	else
	{
		// printf("\033[32mid[%d]\033[0m\n", id);
		// printf("\033[36;mid[%d]\033[0m\n", id + 1);
		data->thrds[id].philo->n_fork
			+= get_fork(data, data->thrds[id + 1].philo->fork, id);
	}
}

int	get_fork(t_data *data, pthread_mutex_t *fork, int id)
{
	pthread_mutex_lock(fork);
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	data->thrds[id].philo->fork_av = FALSE;
	// printf("\033[32mlock-id[%d]\033[0m\n", id);
	print_action(data, FORK, id, ft_get_time(&data->time));
	return (1);
}

int	giveup_fork(pthread_mutex_t *fork, t_data *data, int id)
{
	pthread_mutex_unlock(fork);
	if (data->thrds[id].philo->go_on == FALSE)
		return (0);
	data->thrds[id].philo->fork_av = TRUE;
	// printf("\033[35mlock-id[%d]\033[0m\n", id);
	print_action(data, FORK_LEFT, id, ft_get_time(&data->time));
	return (-1);
}
