/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:44:33 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 17:48:44 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5)
		write(2, "\033[36mError : not enough arguments\n", 33);
	else if (ac < 7)
	{
		data = malloc(sizeof(t_data));
		init_data(data, ac, av);
		make_threads(data);
	}
	else
		write(2, "\033[36mError : too many arguments\n", 31);
	return (0);
}
