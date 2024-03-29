/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:45:15 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/06 15:41:24 by lmicheli         ###   ########.fr       */
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
	DIED,
	FED
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
	long long			start_ms;
	long long			time_since;
}	t_time;

typedef struct s_philo
{
	int					id; // Philo's id.
	int					left_to_eat; // Number of meals left.
	int					n_fork; // Number of forks the philo has.
	t_time				life_left; // Time since last meal.
	t_bool				start; // TRUE if philo has just started.
	t_bool				go_on;	// TRUE if program should continue.
	t_bool				overfed; // TRUE if philo is full.
	t_bool				fork_av; // TRUE if fork is available.
	pthread_mutex_t		fork; // Philo's fork.
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
	int					nb_fed;
	pthread_mutex_t		time_mutex;
	pthread_mutex_t		go_on_mutex;
	pthread_mutex_t		nb_eaten_mutex;
	pthread_mutex_t		end;
	pthread_mutex_t		*fork;
	pthread_mutex_t		mutex;
	pthread_mutex_t		print;
	pthread_mutex_t		check;
	pthread_mutex_t		fork_mutex;
	t_thread			*thrds;
	pthread_t			*thread_alive;
	t_time				time;
	t_bool				go_on;
	t_bool				print_av;
	t_bool				eating;
}	t_data;

typedef struct s_data_id
{
	t_data				*data;
	int					id;
}	t_data_id;

void		print_action(t_data *data, t_action action, int id, long since);
void		prints(t_action action, long time_since, int id, t_data *data);
int			giveup_fork(pthread_mutex_t *fork, t_data *data, int id);
int			get_fork(t_data *data, pthread_mutex_t *fork, int id);
void		destroy_mutexes(t_data *data, int i, t_bool destroy);
void		think_and_die(t_data *data, int id, t_bool both);
void		create_philosopher_thread(t_data *data, int i);
void		input_check(char **av, int ac, t_data *data);
void		init_data(t_data *data, int ac, char **av);
t_bool		go_on_change(t_data *data, t_bool action);
void		check_food(t_data *data, int id, int add);
long		ft_get_time(t_time *start, t_data *data);
void		get_start(t_time *start, t_data *data);
void		fork_acquiring(t_data *data, int id);
void		fork_releasing(t_data *data, int id);
void		mutex_destroy(t_data *data, int i);
t_data_id	*get_data_id(t_data *data, int id);
void		*highlander(t_data *data, int id);
void		satisfied(t_data *data, int id);
void		free_philo(t_data *data, int i);
int			get_food(t_data *data, int id);
void		odd_wait(int id, t_data *data);
void		make_threads(t_data *dataaaa);
int			ft_atoi(const char *strrrr);
size_t		ft_strlen(const char *sss);
void		join_philo(t_data *data);
void		philo_stop(t_data *data);
void		free_all(t_data *data);
void		ft_close(t_data *data);
void		*check_life(void *da);
void		ft_msleep(int time);
void		*routine(void *d);

#endif
