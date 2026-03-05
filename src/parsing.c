/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:58:21 by memillet          #+#    #+#             */
/*   Updated: 2026/03/05 18:39:13 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_data *set, int ac, char **av)
{
	set->nb_eat = -1;
	set->nb_philo = ft_atol(av[1]);
	set->t_die = ft_atol(av[2]);
	set->t_eat = ft_atol(av[3]);
	set->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		set->nb_eat = ft_atol(av[5]);
}

int	check_params(t_data *args)
{
	if (args->nb_philo < 1)
		return (printf("Invalid number of philosophe\n"), 1);
	if (args->t_eat <= 0)
		return (printf("Invalid, time for eat\n"), 1);
	if (args->t_die <= 0)
		return (printf("Invalid time to die\n"), 1);
	if (args->t_sleep <= 0)
		return (printf("Invalid time to sleep\n"), 1);
	if (args-> nb_eat <= 0)
		return (printf("Invalid number of max eat\n"), 1);
	return (0);
}

int	parsing(t_data *args, int ac, char **av)
{
	int	i;

	i = 1;
	while(i < ac)
	{
		if (ft_isdigit(av[i]) != 0)
			return (free(args), printf("Error : Invalid argument\n"), 1);
		i++;
	}
	init_struct(args, ac, av);
	if (check_params(args) != 0)
		return (free(args), 1);
	return (0);
}
