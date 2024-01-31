/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/01/31 11:21:50 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include "../philo.h"

typedef struct s_data_bonus
{
	int					nb_philo; // Number of philosophers.
	int					time_to_die; // Time in ms before a philosopher dies.
	int					time_to_eat; // Time in ms for a philosopher to eat.
	int					time_to_sleep; // Time in ms for a philosopher to sleep.
	int					nb_meals; // Number of meals to eat before stopping.
	t_time				time; // Time struct.
	sem_t				*forks; // Semaphore for forks.
	sem_t				*print; // Semaphore for printing.
	sem_t				*dead; // Semaphore for death.
}	t_data_bonus;

#endif