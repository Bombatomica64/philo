/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:46:21 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 15:58:15 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_current_time_bonus(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	return (time_in_ms);
}

void	ft_msleep_bonus(int time)
{
	long long	tmp;

	tmp = ft_current_time_bonus() + time;
	while (ft_current_time_bonus() < tmp)
		usleep(10);
}

void	get_start_bonus(t_time *start)
{
	gettimeofday(&start->start, NULL);
	start->start_ms = (start->start.tv_sec) * 1000
		+ (start->start.tv_usec) / 1000;
}

long	ft_get_time_bonus(t_time *start)
{
	long			time_since;

	time_since = ft_current_time_bonus() - start->start_ms;
	return (time_since);
}
