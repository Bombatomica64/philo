/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:48:57 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:30:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_data_id_bonus	*data;

	data = (t_data_id_bonus *)arg;
	(void)data;
	return (NULL);
}
