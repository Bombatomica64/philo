/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:45:15 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/22 17:58:21 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum e_error
{
	MALLOC,
	MUTEX,
	THREAD,
	LOW_ARGS,
	TOO_MANY_ARGS,
	NOT_POSITIVE,
	NOT_INT,
	FORK_M
}	t_error;

typedef enum e_action
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DIED
}	t_action;

typedef enum e_bool
{
	FALSE,
	TRUE,
	ERROR = -1
}	t_bool;

typedef struct s_time
{
	struct timeval		start;
	long				start_ms;
	long				time_since;
}	t_time;

typedef struct s_philo
{
	int					id;
	int					left_to_eat;
	int					n_fork;
	t_time				life_left;
	t_bool				start;
	t_bool				alive;
	pthread_mutex_t		fork;
}	t_philo;

typedef struct s_thread
{
	pthread_t			*thread;
	t_philo				*philo;
}	t_thread;

typedef struct s_data
{
	int					nb_philo;
	int					nb_fork;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat;
	t_thread			*thrds;
	pthread_t			*thread_alive;
	t_time				time;
	t_bool				go_on;
	pthread_mutex_t		*print;
}	t_data;

typedef struct s_data_id
{
	t_data				*data;
	int					id;
}	t_data_id;

int		ft_atoi(const char *str);
long	ft_get_time(t_time *st);
int		get_fork(t_data *data, pthread_mutex_t *fork, int id);
int		giveup_fork(pthread_mutex_t *fork);
void	init_data(t_data *data, int ac, char **av);
void	input_check(char **av, int ac, t_data *data);
void	make_threads(t_data *data);
void	fork_acquiring(t_data *data, t_data_id *all);
void	fork_releasing(t_data *data, t_data_id *all);
void	free_all(t_data *data);
void	free_philo(t_data *data, int i);
void	mutex_destroy(t_data *data, int i);
void	print_action(t_data *data, t_action action, int id, long time_since);
void	*check_life(void *da);
void	ft_msleep(int time);
void	get_start(t_time *start);

#endif
