/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:30 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:34:58 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	fake_atoi_bonus(char *str, long long int *nbr)
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

int	ft_check_for_non_int_bonus(char *str)
{
	long long int	nbr;
	int				i;

	i = 1;
	nbr = 0;
	if (ft_strlen(str) > 11)
		return (0);
	i = fake_atoi_bonus(str, &nbr);
	return (i);
}

void	input_check_bonus(char **av, int ac, t_data_bonus *data)
{
	if (ft_check_for_non_int_bonus(av[1]) == 0)
		write(2, "\033[36mError : philosophers must be an integer\n", 45);
	else if (ft_check_for_non_int_bonus(av[2]) == 0)
		write(2, "\033[36mError : time to die must be an integer\n", 45);
	else if (ft_check_for_non_int_bonus(av[3]) == 0)
		write(2, "\033[36mError : time to eat must be an integer\n", 45);
	else if (ft_check_for_non_int_bonus(av[4]) == 0)
		write(2, "\033[36mError : time to sleep must be an integer\n", 47);
	else if (ac == 6 && ft_check_for_non_int_bonus(av[5]) == 0)
		write(2, "\033[36mError : Number of plates must be an integer\n", 51);
	else
		return ;
	free(data);
	exit(EXIT_FAILURE);
}

void	init_data_bonus(t_data_bonus *data, int ac, char **av)
{
	input_check_bonus(av, ac, data);
	data = malloc(sizeof(t_data_bonus));
	data->nb_philo = ft_atoi_bonus(av[1]);
	data->time_to_die = ft_atoi_bonus(av[2]);
	data->time_to_eat = ft_atoi_bonus(av[3]);
	data->time_to_sleep = ft_atoi_bonus(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi_bonus(av[5]);
	else
		data->nb_meals = -4666;
	data->philo = malloc(sizeof(t_philo_bonus) * data->nb_philo);
	get_start_bonus(&data->time);
}
