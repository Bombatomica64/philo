/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:10:10 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:31:03 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_data_bonus	*data;

	if (ac < 5)
		write(2, "\033[36mError : not enough arguments\n", 33);
	else if (ac < 7)
	{
		data = malloc(sizeof(t_data_bonus));
		init_data_bonus(data, ac, av);
		make_semaphores(data);
		make_processes(data);
	}
	else
		write(2, "\033[36mError : too many arguments\n", 31);
	return (0);
}
