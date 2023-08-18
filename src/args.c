/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:30:57 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/18 01:24:53 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}

int	check_args(t_common common, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (is_all_digit(av[i]) == RETURN_FAILURE)
			return (RETURN_FAILURE);
		i++;
	}
	if (common.number_of_philosophers < 1)
		return (RETURN_FAILURE);
	if (common.time.time_to_die < 0)
		return (RETURN_FAILURE);
	if (common.time.time_to_eat < 0)
		return (RETURN_FAILURE);
	if (common.time.time_to_sleep < 0)
		return (RETURN_FAILURE);
	if (common.nbr_meals_to_eat == -1 && ac == 6)
		return (RETURN_FAILURE);
	if (common.nbr_meals_to_eat == 0 && ac == 5)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
