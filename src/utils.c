/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:34 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/17 04:56:18 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	get_time_since_start(t_common common)
{
	return (get_time() - common.time.start_time);
}

int	check_is_dead(t_is_dead	is_dead)
{
	int	return_code;

	pthread_mutex_lock(&(is_dead.lock));
	return_code = *(is_dead.value);
	pthread_mutex_unlock(&(is_dead.lock));
	return (return_code);
}

int	display_error_msg(int fd, char *str, int return_code)
{
	int	len;

	if (str == NULL)
		return (return_code);
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
	return (return_code);
}
