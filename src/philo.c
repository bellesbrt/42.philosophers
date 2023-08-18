/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:17 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/06 23:47:16 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	create_one_philo(t_philo *args)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, &philo_routine, args);
	return (thread_id);
}

pthread_t	*launch_philos(int number_philosophers, t_philo *philos)
{
	pthread_t	*philos_pid;
	int			i;

	if (philos == NULL)
		return (NULL);
	philos_pid = malloc(sizeof(*philos_pid) * (number_philosophers + 1));
	if (philos_pid == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	if (number_philosophers == 1)
	{
		pthread_create(&philos_pid[0], NULL, &routine_one_philo, &philos[0]);
		return (philos_pid);
	}
	i = 0;
	while (i < number_philosophers)
	{
		philos_pid[i] = create_one_philo(&philos[i]);
		i++;
	}
	return (philos_pid);
}
