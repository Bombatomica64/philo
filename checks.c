/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:16:42 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/17 15:19:38 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	input_check(t_data *data)
{
	if (data->time_to_die < 0)
		write(2, "\033[36mError : time to die must be positive\n", 42);
	else if (data->time_to_eat < 0)
		write(2, "\033[36mError : time to eat must be positive\n", 42);
	else if (data->time_to_sleep < 0)
		write(2, "\033[36mError : time to sleep must be positive\n", 44);
	else if (data->nb_eat < 0 || data->nb_eat != -100)
		write(2, "\033[36mError : number of meals must be positive\n", 47);
	else
		return ;
	free_all(data);
	exit(EXIT_FAILURE);
}
