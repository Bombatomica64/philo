/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:45:15 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/17 15:35:01 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define FORK 1
# define TIME_TO_DIE 1000
# define TIME_TO_EAT 200
# define TIME_TO_SLEEP 200

typedef struct s_philo
{
	int					id;
	int					left_to_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	pthread_mutex_t		*dead;
	t_time				life;
}	t_philo;

typedef struct s_thread
{
	pthread_t			*thread;
	t_philo				*philo;
}	t_thread;

typedef struct s_time
{
	struct timeval		start;
	struct timeval		now;
}	t_time;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	t_thread		*threads;
}	t_data;

int		ft_atoi(const char *str);
void	init_data(t_data *data, int ac, char **av);
void	input_check(t_data *data);

#endif