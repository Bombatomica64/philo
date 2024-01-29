/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:42:05 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/29 17:13:16 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	fake_atoi(char *str, long long int *nbr)
{
	int				i;
	int				flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if ((str[0] == '-' || str[0] == '+') && flag == 0)
		{
			if (str[i] == '-')
				flag = -1;
			else if (str[i] == '+')
				flag = 1;
			if (str[i + 1] < '0' || str[i + 1] > '9')
				return (0);
			i++;
		}
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		*nbr = *nbr * 10 + (str[i] - '0');
		i++;
	}
	if (flag * *nbr > 2147483647 || flag * *nbr < -2147483648)
		return (FALSE);
	return (TRUE);
}

int	ft_check_for_non_int(char *str)
{
	long long int	nbr;
	int				i;

	i = 1;
	nbr = 0;
	if (ft_strlen(str) > 11)
		return (0);
	i = fake_atoi(str, &nbr);
	return (i);
}

void	input_check(char **av, int ac, t_data *data)
{
	if (ft_check_for_non_int(av[1]) == 0)
		write(2, "\033[36mError : philosophers must be an integer\n", 45);
	else if (ft_check_for_non_int(av[2]) == 0)
		write(2, "\033[36mError : time to die must be an integer\n", 45);
	else if (ft_check_for_non_int(av[3]) == 0)
		write(2, "\033[36mError : time to eat must be an integer\n", 45);
	else if (ft_check_for_non_int(av[4]) == 0)
		write(2, "\033[36mError : time to sleep must be an integer\n", 47);
	else if (ac == 6 && ft_check_for_non_int(av[5]) == 0)
		write(2, "\033[36mError : Number of plates must be an integer\n", 51);
	else
		return ;
	free(data);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data, int ac, char **av)
{
	input_check(av, ac, data);
	data->nb_philo = atoi(av[1]);
	data->nb_fork = data->nb_philo;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->go_on = TRUE;
	if (ac == 6)
		data->nb_eat = ft_atoi(av[5]);
	else
		data->nb_eat = -4666;
	pthread_mutex_init(&data->go_on_mutex, NULL);
	data->eating = TRUE;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->end, NULL);
}
