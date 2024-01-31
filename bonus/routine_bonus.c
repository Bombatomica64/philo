/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:50:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_eat(t_data_bonus *data, int id)
{
	take_fork(data, id);
	take_fork(data, id);
	sem_wait(data->print);
	printf("%ld %d is eating\n", ft_get_time_bonus(&data->time), id);
	sem_post(data->print);
	data->philo[id].nb_meals++;
	get_start_bonus(&data->philo[id].life_left);
	ft_msleep_bonus(data->time_to_eat);
	leave_fork(data, id);
	leave_fork(data, id);
}

void	leave_fork(t_data_bonus *data, int id)
{
	(void)id;
	sem_post(data->forks);
}

void	take_fork(t_data_bonus *data, int id)
{
	sem_wait(data->forks);
	sem_wait(data->print);
	printf("%ld %d has taken a fork\n", ft_get_time_bonus(&data->time), id);
	sem_post(data->print);
}

t_data_id_bonus	*make_data_id(t_data_bonus *data, int id)
{
	t_data_id_bonus	*data_id;

	data_id = malloc(sizeof(t_data_id_bonus));
	data_id->data = data;
	data_id->id = id;
	return (data_id);
}

void	philo_life(t_data_bonus *data, int id)
{
	pthread_create(&data->philo[id].thread, NULL,
		&check_death, make_data_id(data, id));
	while (data->philo[id].go_on)
	{
		philo_eat(data, id);
	}
}
