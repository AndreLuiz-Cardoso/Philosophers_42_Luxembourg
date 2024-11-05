/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancardos <ancardos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:31 by ancardos          #+#    #+#             */
/*   Updated: 2024/09/13 11:04:18 by ancardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	pthread_mutex_t	*m_forks;
	t_philosopher	*philos;
	t_status		status;

	if (!is_valid_input(argc, argv))
	{
		printf("Invalid args: usage is <nbr_of_philo>(>= 1) "\
		"<time_to_die>(>= 1) <time_to_eat>(>= 1) "\
		"<time_to_sleep>(>= 1) <must_eat>(optional).\n");
		return (EXIT_FAILURE);
	}
	init_status(argv, &status);
	m_forks = init_forks(&status);
	if (!m_forks)
		return (EXIT_FAILURE);
	philos = init_philosophers(&status, &m_forks);
	if (!philos)
	{
		free(m_forks);
		return (EXIT_FAILURE);
	}
	set_dinner(&status, philos);
	free_data(philos, m_forks);
	return (0);
}

void	free_data(t_philosopher *philos, pthread_mutex_t *m_forks)
{
	size_t	i;
	size_t	total_philos;

	i = 0;
	total_philos = philos[0].status->total_philo;
	while (i < total_philos)
	{
		pthread_mutex_destroy(&m_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos[0].status->m_print_status);
	pthread_mutex_destroy(&philos[0].status->m_meals_repeated);
	pthread_mutex_destroy(&philos[0].status->m_stop_dinner);
	pthread_mutex_destroy(&philos[0].status->m_last_meal);
	free(m_forks);
	free(philos);
}
