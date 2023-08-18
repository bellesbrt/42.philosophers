/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:19 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/06 23:47:44 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *data)
{
	pthread_mutex_lock(data->common.output);
	if (!*(data->common.is_dead))
		printf("%d %d is sleeping\n", get_time_since_start(data->common),
			data->philo_id);
	pthread_mutex_unlock(data->common.output);
	ft_usleep(data->common.time.time_to_sleep * 1000, data);
}

int	philo_eat(t_philo *data)
{
	if (take_forks(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	output_eat(data);
	pthread_mutex_lock(&(data->update_status));
	data->time_of_last_meal = get_time_since_start(data->common);
	pthread_mutex_unlock(&(data->update_status));
	ft_usleep(data->common.time.time_to_eat * 1000, data);
	pthread_mutex_lock(&(data->update_status));
	data->nbr_meals_eaten++;
	pthread_mutex_unlock(&(data->update_status));
	pthread_mutex_lock(&(data->fork_left->fork));
	data->fork_left->fork_is_used = false;
	pthread_mutex_unlock(&(data->fork_left->fork));
	pthread_mutex_lock(&(data->fork_right->fork));
	data->fork_right->fork_is_used = false;
	pthread_mutex_unlock(&(data->fork_right->fork));
	return (RETURN_SUCCESS);
}

void	philo_think(t_philo *data)
{
	int	time_to_think;

	time_to_think = (data->time_of_last_meal + data->common.time.time_to_die
			- data->common.time.time_to_sleep
			- get_time_since_start(data->common)) / 2;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > MAX_TIME_THINK)
		time_to_think = MAX_TIME_THINK;
	pthread_mutex_lock(data->common.output);
	if (!*(data->common.is_dead))
		printf("%d %d is thinking\n", get_time_since_start(data->common),
			data->philo_id);
	pthread_mutex_unlock(data->common.output);
	ft_usleep(time_to_think * 1000, data);
}

void	think_and_eat(t_philo *data)
{
	while (!*(data->common.is_dead) && philo_eat(data) != RETURN_SUCCESS)
		philo_think(data);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->common.output);
	if (!*(philo->common.is_dead))
		printf("%d %d is thinking\n", get_time_since_start(philo->common),
			philo->philo_id);
	pthread_mutex_unlock(philo->common.output);
	if (philo->philo_id % 2 == 0)
		ft_usleep(SMALL_WAIT, data);
	while (continue_loop(philo) == RETURN_SUCCESS)
	{
		while (philo_eat(philo) != RETURN_SUCCESS)
			(void)philo;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
