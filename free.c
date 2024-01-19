/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:22:58 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/19 17:54:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_data *data)
{
	int	i;
	while (i < data->nb_fork)
	{
		pthread_mutex_destroy(data->thrds[i].philo->fork);
		free(data->thrds[i].philo);
		i++;
	}
	printf("free\n");
}
