/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:54:40 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/29 16:29:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_action(t_data *data, t_bool action, t_bool *tmp)
{
	pthread_mutex_lock(&data->go_on_mutex);
	if (action == TRUE)
	{
		data->go_on = FALSE;
		philo_stop(data);
	}
	else if (action == FALSE)
	{
		*tmp = data->go_on;
	}
	pthread_mutex_unlock(&data->go_on_mutex);
}

t_bool	go_on_change(t_data *data, t_bool action)
{
	t_bool			tmp;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	if (data->go_on == FALSE)
	{
		pthread_mutex_unlock(&mutex);
		pthread_mutex_destroy(&mutex);
		return (FALSE);
	}
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	handle_action(data, action, &tmp);
	if (action == TRUE || action == ERROR)
	{
		return (FALSE);
	}
	else if (action == FALSE)
	{
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
