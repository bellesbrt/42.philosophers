/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:43:49 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/18 01:30:51 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define DEAD_PHILO 1
# define DONT_STOP 0
# define NO_MORE_MEALS 2

# define SMALL_WAIT	100
# define USLEEP_MAX_CYCLE_LENGHT 10000
# define MAX_TIME_THINK 2000
# define SMALL_SLEEP 100
# define LONG_SLEEP 100

# define STOP_SIMULATION 1

# define RETURN_SUCCESS EXIT_SUCCESS
# define RETURN_FAILURE EXIT_FAILURE

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_time_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
}					t_time_data;

typedef struct s_is_dead
{
	t_bool			*value;
	pthread_mutex_t	lock;
}					t_is_dead;

typedef struct s_common
{
	t_bool			*is_dead;
	int				nbr_meals_to_eat;
	int				nbr_philo_meals_finished;
	int				number_of_philosophers;
	t_time_data		time;
	pthread_mutex_t	*output;
}					t_common;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	t_bool			fork_is_used;
}					t_fork;

typedef struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	t_fork			*fork_left;
	t_fork			*fork_right;
	int				time_of_last_meal;
	int				nbr_meals_eaten;
	t_common		common;
	pthread_mutex_t	update_status;
}					t_philo;

typedef struct s_monitor
{
	t_common		*common;
	t_philo			**philo_struct;
}					t_monitor;

typedef struct s_main
{
	t_common		common;
	t_bool			is_dead;
	t_fork			*forks;
	t_philo			*philo_struct;
	pthread_t		*pid_threads;
	pthread_mutex_t	output;
	t_monitor		monitor_args;
}					t_main;

void				clean_philos(t_philo *philos, pthread_t *threads_pid,
						t_fork *forks);

int					ft_atoi(const char *str);
int					ft_isdigit(int c);

void				*monitor(void *data);
pthread_t			launch_monitor(t_philo **philo_struct, t_common *common,
						t_monitor *monitor_args);

pthread_t			*launch_philos(int number_philosophers, t_philo *philos);

int					continue_loop(t_philo *data);
int					take_forks(t_philo *data);
void				output_eat(t_philo *data);
void				*routine_one_philo(void *data);

void				*philo_routine(void *data);

void				ft_usleep(useconds_t time, t_philo *data);

int					get_time(void);
int					get_time_since_start(t_common common);
int					check_args(t_common common, int ac, char **av);
int					display_error_msg(int fd, char *str, int return_code);

#endif