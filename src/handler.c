/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:01 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/18 01:28:07 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return ((c == '\t' || \
		c == '\n' || \
		c == '\v' || \
		c == '\f' || \
		c == '\r' || \
		c == ' '));
}

int	ft_atoi(const char *str)
{
	int			sign;
	size_t		i;
	long long	result;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return ((int)result * sign);
}

void	clean_philos(t_philo *philos, pthread_t *threads_pid, t_fork *forks)
{
	free(philos);
	free(threads_pid);
	free(forks);
}
