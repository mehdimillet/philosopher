/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:08:19 by memillet          #+#    #+#             */
/*   Updated: 2026/03/19 10:46:00 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	init_int(int *full, int *i)
{
	*full = 0;
	*i = 0;
}

static bool	check_full(t_data *data, int full)
{
	if (full == data->nb_philo)
		return (ft_is_full(data), false);
	usleep(100);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->info->t_eat * 1000);
	while (1)
	{
		if (ft_eat(philo) != true)
			return (NULL);
		if (ft_sleep(philo) != true)
			return (NULL);
		if (ft_think(philo) != true)
			return (NULL);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data		*data;
	int			i;
	int			full;
	int			n_eat;
	long long	tmp;

	data = (t_data *)arg;
	while (1)
	{
		init_int(&full, &i);
		while (i < data->nb_philo)
		{
			ft_have_tmp(&data->philo[i], &tmp, &n_eat);
			pthread_mutex_lock(&data->mutex);
			if (tmp > data->t_die)
				return (ft_is_dead(data, i), NULL);
			if ((data->nb_eat != -1) && n_eat >= data->nb_eat)
				full++;
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
		if (check_full(data, full) == false)
			return (NULL);
	}
	return (NULL);
}

void	thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread_id, NULL,
			routine, &data->philo[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}
