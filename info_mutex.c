/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:54:40 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/29 12:57:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	go_on_change(t_data *data, t_bool action)
{
	t_bool	tmp;

	pthread_mutex_lock(&data->go_on_mutex);
	if (action == TRUE)
	{
		data->go_on = FALSE;
		philo_stop(data);
		pthread_mutex_unlock(&data->go_on_mutex);
		return (FALSE);
	}
	else if (action == ERROR)
	{
		pthread_mutex_unlock(&data->go_on_mutex);
		pthread_mutex_destroy(&data->go_on_mutex);
		return (FALSE);
	}
	else if (action == FALSE)
	{
		tmp = data->go_on;
		pthread_mutex_unlock(&data->go_on_mutex);
		return (tmp);
	}
	return (ERROR);
}

void	number_of_times_eaten(t_data *data, int id, t_bool eat)
{
	pthread_mutex_lock(&data->nb_eaten_mutex);
	data->eating = FALSE;
	if (eat == TRUE)
	{
		data->thrds[id].philo->left_to_eat--;
		pthread_mutex_unlock(&data->nb_eaten_mutex);
		data->eating = TRUE;
		return ;
	}
	satisfied(data, id);
	pthread_mutex_unlock(&data->nb_eaten_mutex);
	data->eating = TRUE;
}

void	satisfied(t_data *data, int id)
{
	int		i;

	if (data->thrds[id].philo->left_to_eat == 0)
	{
		data->thrds[id].philo->overfed = TRUE;
		i = 0;
		while (i < data->nb_philo)
		{
			if (data->thrds[i].philo->left_to_eat == 0)
				i++;
			else
				break ;
		}
		if (i == data->nb_philo)
		{
			print_action(data, FED, id, ft_get_time(&data->time));
			go_on_change(data, TRUE);
		}
	}
}
