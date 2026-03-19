/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:50:29 by memillet          #+#    #+#             */
/*   Updated: 2026/03/19 10:18:28 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = malloc(sizeof(t_data));
		if (!data)
			return (1);
		if (parsing(data, ac, av) == 1)
			return (free(data), 1);
		thread(data);
		free(data->philo);
		free(data->forks);
		free(data);
	}
	else
		printf("Invalide number of arguments\n");
	return (0);
}
