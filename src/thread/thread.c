/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:08:19 by memillet          #+#    #+#             */
/*   Updated: 2026/03/16 12:47:56 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	ft_is_full(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->mutex);
}

static void	ft_is_dead(t_data *data, int i)
{
	data->dead = 1;
	printf("%2lld Philo%d is dead\n",(get_time() - data->t_start) ,data->philo[i].id);
	pthread_mutex_unlock(&data->mutex);
}

static void	ft_have_tmp(t_philo *philo, long long *tmp, int *n_eat)
{
	pthread_mutex_lock(&philo->mutex);
	*tmp = get_time() - philo->last_eat;
	*n_eat = philo->n_eat; 
	pthread_mutex_unlock(&philo->mutex);
}

void	*routine(void *arg)
{
	t_philo *philo;

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
		full = 0;
		i = 0;
		while(i < data->nb_philo)
		{
			ft_have_tmp(&data->philo[i], &tmp, &n_eat);
			pthread_mutex_lock(&data->mutex);
			if (tmp > data->t_die)
				return (ft_is_dead(data, i) ,NULL);
			if ((data->nb_eat != -1) && n_eat >= data->nb_eat)
				full++;
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
		if (full == data->nb_philo)
			return (ft_is_full(data) ,NULL);
		usleep(100);
	}
	return (NULL);
}

void	thread(t_data *data)
{
	int i;
	int	error;

	i = 0;
	while (i < data->nb_philo)
	{
		error = pthread_create(&data->philo[i].thread_id, NULL, routine, &data->philo[i]);
		if (error != 0)
			return ;
		i++;
	}
	error = pthread_create(&data->monitor, NULL, monitor_routine, data);
	if (error != 0)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		error = pthread_join(data->philo[i].thread_id, NULL);
		if (error != 0)
			return ;
		i++;
	}
	error = pthread_join(data->monitor, NULL);
	if (error != 0)
		return ;
}
