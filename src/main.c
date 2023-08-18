/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:31:07 by inicole-          #+#    #+#             */
/*   Updated: 2023/08/17 04:39:40 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo_struct(t_fork *forks, t_common common)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(*philo) * common.number_of_philosophers);
	if (philo == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i < common.number_of_philosophers)
	{
		philo[i].philo_id = i + 1;
		philo[i].fork_left = &forks[i];
		if (philo[i].philo_id == common.number_of_philosophers)
			philo[i].fork_right = &forks[0];
		else
			philo[i].fork_right = &forks[i + 1];
		philo[i].time_of_last_meal = 0;
		philo[i].nbr_meals_eaten = 0;
		philo[i].common = common;
		pthread_mutex_init(&philo[i].update_status, NULL);
		i++;
	}
	return (philo);
}

t_common	fill_args(int ac, char **av, t_bool *is_dead,
		pthread_mutex_t *output)
{
	t_common	common;
	t_time_data	time_data;

	pthread_mutex_init(output, NULL);
	common.output = output;
	common.number_of_philosophers = ft_atoi(av[1]);
	time_data.time_to_die = ft_atoi(av[2]);
	time_data.time_to_eat = ft_atoi(av[3]);
	time_data.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		common.nbr_meals_to_eat = ft_atoi(av[5]);
	else
		common.nbr_meals_to_eat = -1;
	time_data.start_time = get_time();
	common.is_dead = is_dead;
	common.time = time_data;
	common.nbr_philo_meals_finished = 0;
	return (common);
}

t_fork	*create_forks(int number_philosophers)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(*forks) * (number_philosophers + 1));
	if (forks == NULL)
	{
		printf("Error: malloc() failed");
		return (NULL);
	}
	i = 0;
	while (i < number_philosophers)
	{
		pthread_mutex_init(&forks[i].fork, NULL);
		forks[i].fork_is_used = false;
		i++;
	}
	return (forks);
}

void	join_threads(pthread_t *pid_threads, int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(pid_threads[i], NULL);
		i++;
	}
	pthread_join(pid_threads[number_of_philosophers], NULL);
}

int	main(int ac, char **av)
{
	t_main	main;

	if (ac < 5 || ac > 6)
		return (EXIT_FAILURE);
	main.is_dead = false;
	main.common = fill_args(ac, av, &main.is_dead, &main.output);
	if (check_args(main.common, ac, av) == RETURN_FAILURE)
		return (EXIT_SUCCESS);
	main.forks = create_forks(main.common.number_of_philosophers);
	if (main.forks == NULL)
		return (EXIT_FAILURE);
	main.philo_struct = create_philo_struct(main.forks, main.common);
	main.pid_threads = launch_philos(main.common.number_of_philosophers,
			main.philo_struct);
	if (main.pid_threads == NULL)
	{
		clean_philos(main.philo_struct, main.pid_threads, main.forks);
		return (EXIT_FAILURE);
	}
	main.pid_threads[main.common.number_of_philosophers]
		= launch_monitor(&main.philo_struct, &main.common, &main.monitor_args);
	join_threads(main.pid_threads, main.common.number_of_philosophers);
	clean_philos(main.philo_struct, main.pid_threads, main.forks);
	return (EXIT_SUCCESS);
}
