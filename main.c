/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:44:33 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/17 15:17:10 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
		write(2, "\033[36mError : not enough arguments\n", 33);
	else if (ac > 6)
	{
		init_data(&data, ac, av);
		input_check(&data);
		make_threads(&data);
	}
}
