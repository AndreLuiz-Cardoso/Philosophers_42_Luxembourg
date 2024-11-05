/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancardos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:38 by ancardos          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:39 by ancardos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_valid_input(int argc, char **argv)
{
	size_t	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (FALSE);
	while (i < (size_t) argc)
	{
		if (!is_natural_nbr(argv[i]) || *argv[1] == '0' \
			|| *argv[2] == '0' || *argv[3] == '0' || *argv[4] == '0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

size_t	to_natural_nbr(char *str)
{
	size_t	nbr_conv;

	nbr_conv = 0;
	while (*str)
	{
		nbr_conv = (nbr_conv * 10) + (*str - '0');
		str++;
	}
	return (nbr_conv);
}

t_bool	is_natural_nbr(char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		if (!ft_isdigit(string[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}
