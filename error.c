/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:23:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/19 17:49:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_data *data, t_error error_type)
{
	if (error_type == MALLOC)
		write(2, "\033[36mError : malloc failed\n", 27);
	else if (error_type == MUTEX)
		write(2, "\033[36mError : mutex failed\n", 26);
	else if (error_type == THREAD)
		write(2, "\033[36mError : thread failed\n", 27);
	else if (error_type == LOW_ARGS)
		write(2, "\033[36mError : not enough arguments\n", 33);
	else if (error_type == TOO_MANY_ARGS)
		write(2, "\033[36mError : too many arguments\n", 31);
	else if (error_type == NOT_POSITIVE)
		write(2, "\033[36mError : arguments must be positive\n", 40);
	else if (error_type == NOT_INT)
		write(2, "\033[36mError : arguments must be numbers\n", 38);
	else if (error_type == FORK_M)
		write(2, "\033[36mError : Fork mutex failed\n", 47);
	else if (error_type == THREAD)
		write(2, "\033[36mError : thread failed\n", 49);
	free_all(data);
	exit(EXIT_FAILURE);
}
