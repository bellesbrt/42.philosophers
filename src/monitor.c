/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:14 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/17 04:28:53 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_simulation(t_philo *philo)
{
	int	return_code;

	pthread_mutex_lock(&philo->update_status);
	return_code = DONT_STOP;
	if (philo->common.nbr_meals_to_eat != -1
		&& philo->nbr_meals_eaten >= philo->common.nbr_meals_to_eat)
		return_code = NO_MORE_MEALS;
	else if (get_time_since_start(philo->common)
		- philo->time_of_last_meal >= philo->common.time.time_to_die)
		return_code = DEAD_PHILO;
	pthread_mutex_unlock(&philo->update_status);
	return (return_code);
}

pthread_t	launch_monitor(t_philo **philo_struct, t_common *common,
	t_monitor *monitor_args)
{
	pthread_t	monitor_id;

	monitor_args->philo_struct = philo_struct;
	monitor_args->common = common;
	pthread_create(&monitor_id, NULL, monitor, monitor_args);
	return (monitor_id);
}

int	process_simulation_return(int stop_simulation_return,
	t_monitor *monitor, t_philo *philo_struct, int *i)
{
	if (stop_simulation_return == DEAD_PHILO)
	{
		pthread_mutex_lock(monitor->common->output);
		*(monitor->common->is_dead) = 1;
		printf("%d %d died\n",
			get_time_since_start(*(monitor->common)),
			philo_struct[*i].philo_id);
		pthread_mutex_unlock(monitor->common->output);
		return (RETURN_FAILURE);
	}
	if (stop_simulation_return == NO_MORE_MEALS)
	{
		monitor->common->nbr_philo_meals_finished++;
		if (monitor->common->nbr_philo_meals_finished
			== monitor->common->number_of_philosophers)
			return (RETURN_FAILURE);
	}
	else if (stop_simulation_return == DONT_STOP)
	{
		monitor->common->nbr_philo_meals_finished = 0;
		(*i)++;
	}
	return (RETURN_SUCCESS);
}

void	*monitor(void *data)
{
	t_monitor	*monitor;
	t_philo		*philo_struct;
	int			i;
	int			stop_simulation_return ;

	monitor = (t_monitor *)data;
	if (monitor->common->number_of_philosophers == 1)
		return (NULL);
	philo_struct = *(monitor->philo_struct);
	while (1)
	{
		i = 0;
		while (i < monitor->common->number_of_philosophers)
		{
			stop_simulation_return = stop_simulation(&philo_struct[i]);
			if (process_simulation_return(stop_simulation_return, monitor,
					philo_struct, &i) == RETURN_FAILURE)
				return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
