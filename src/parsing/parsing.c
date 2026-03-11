/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 00:58:21 by memillet          #+#    #+#             */
/*   Updated: 2026/03/11 15:23:30 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_data *data, int ac, char **av)
{
	data->nb_eat = -1;
	data->nb_philo = ft_atol(av[1]);
	data->t_die = ft_atol(av[2]);
	data->t_eat = ft_atol(av[3]);
	data->t_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->nb_eat = ft_atol(av[5]);
	data->dead = 0;
}

int	check_params(t_data *data)
{
	if (data->nb_philo < 1)
		return (printf("Invalid number of philosophe\n"), 1);
	if (data->t_eat <= 0)
		return (printf("Invalid, time for eat\n"), 1);
	if (data->t_die <= 0)
		return (printf("Invalid time to die\n"), 1);
	if (data->t_sleep <= 0)
		return (printf("Invalid time to sleep\n"), 1);
	if (data->nb_eat != -1 && data-> nb_eat <= 0)
		return (printf("Invalid number of max eat\n"), 1);
	return (0);
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = get_time();
	if (data->t_start == -1)
		return ;
	data->philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->philo)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * (data->nb_philo));
	if (!data->forks)
		return (free(data->philo));
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].n_eat = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->nb_philo;
		data->philo[i]. last_eat = data->t_start;
		data->philo[i].info = data;
		i++;
	}
}

int	parsing(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	while(i < ac)
	{
		if (ft_isdigit(av[i]) != 0)
			return (free(data), printf("Error : Invalid argument\n"), 1);
		i++;
	}
	init_struct(data, ac, av);
	if (check_params(data) != 0)
		return (free(data), 1);
	init_data(data);
	return (0);
}

