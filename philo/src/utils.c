/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancardos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:58 by ancardos          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:59 by ancardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mssleep(size_t ms_time)
{
	size_t			start;
	struct timespec	req;

	start = get_current_time();
	while (ms_time > get_current_time() - start)
	{
		req.tv_sec = 0;
		req.tv_nsec = 1000000L;
		nanosleep(&req, NULL);
	}
}
