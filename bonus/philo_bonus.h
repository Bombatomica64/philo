/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 17:34:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include "../philo.h"

typedef struct s_philo_bonus
{
	int					id; // Philosopher id.
	int					nb_meals; // Number of meals eaten.
	pid_t				pid; // Philosopher pid.
	pthread_t			thread; // Philosopher thread.
	t_time				life_left; // Time left before death.
	t_bool				dead; // Boolean for death.
	t_bool				overfed; // Boolean for fed.
	t_bool				go_on; // Boolean for continuing.
}	t_philo_bonus;

typedef struct s_data_bonus
{
	int					nb_philo; // Number of philosophers.
	int					time_to_die; // Time in ms before a philosopher dies.
	int					time_to_eat; // Time in ms for a philosopher to eat.
	int					time_to_sleep; // Time in ms for a philosopher to sleep.
	int					nb_meals; // Number of meals to eat before stopping.
	t_time				time; // Time struct.
	t_philo_bonus		*philo; // Philosopher struct.
	sem_t				*forks; // Semaphore for forks.
	sem_t				*print; // Semaphore for printing.
	sem_t				*dead; // Semaphore for death.
	sem_t				*end; // Semaphore for ending.
}	t_data_bonus;

typedef struct s_data_id_bonus
{
	t_data_bonus		*data; // Data struct.
	int					id; // Philosopher id.
}	t_data_id_bonus;

void	input_check_bonus(char **av, int ac, t_data_bonus *data);
void	init_data_bonus(t_data_bonus *data, int ac, char **av);
void	philo_life(t_data_bonus *data, int id);
void	leave_fork(t_data_bonus *data, int id);
void	philo_eat(t_data_bonus *data, int id);
void	take_fork(t_data_bonus *data, int id);
void	take_fork(t_data_bonus *data, int id);
void	make_semaphores(t_data_bonus *data);
void	make_processes(t_data_bonus *data);
long	ft_get_time_bonus(t_time *start);
void	get_start_bonus(t_time *start);
void	ft_msleep_bonus(int time);
void	*check_death(void *arg);
int		ft_atoi_bonus(const char *str);

#endif