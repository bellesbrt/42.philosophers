/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:37 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/06 23:47:53 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned int time, t_philo *data)
{
	int	start_time;
	int	target_time_ms;
	int	i;

	i = 0;
	start_time = get_time_since_start(data->common);
	target_time_ms = time / 1000;
	if (target_time_ms <= 0)
		return ;
	while (get_time_since_start(data->common) - start_time < target_time_ms)
	{
		if (i == (1000 / SMALL_SLEEP * 1000))
		{
			i = 0;
			pthread_mutex_lock(data->common.output);
			if (*(data->common.is_dead))
			{
				pthread_mutex_unlock(data->common.output);
				return ;
			}
			pthread_mutex_unlock(data->common.output);
		}
		usleep(SMALL_SLEEP);
		i++;
	}
}
