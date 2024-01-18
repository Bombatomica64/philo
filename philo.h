/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:45:15 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/17 17:51:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED
}	t_action;

typedef struct s_time
{
	struct timeval		start;
	int					time_since;
}	t_time;

typedef struct s_philo
{
	int					id;
	int					left_to_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*dead;
	t_time				life;
}	t_philo;

typedef struct s_thread
{
	pthread_t			*thread;
	t_philo				*philo;
}	t_thread;

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	t_thread			*thrds;
	t_time				time;
	pthread_mutex_t		*print;
}	t_data;

int		ft_atoi(const char *str);
void	init_data(t_data *data, int ac, char **av);
void	input_check(t_data *data);
void	make_threads(t_data *data);
void	free_all(t_data *data);

#endif
