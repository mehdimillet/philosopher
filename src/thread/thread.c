/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 12:08:19 by memillet          #+#    #+#             */
/*   Updated: 2026/03/11 15:33:14 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

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
			printf("full = %d\n", full);
			ft_have_tmp(&data->philo[i], &tmp, &n_eat);
			pthread_mutex_lock(&data->mutex);
			if (tmp > data->t_die)
			{
				data->dead = 1;
				printf("%2lld Philo%d is dead\n",get_time() ,data->philo[i].id);
				pthread_mutex_unlock(&data->mutex);
				return (NULL);
			}
			if ((data->nb_eat != -1))
				full++;
			pthread_mutex_unlock(&data->mutex);
			i++;
		}
		if (full == data->nb_philo)
			return (NULL);
		usleep(10);
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
		error = pthread_join(data->monitor, NULL);
		if (error != 0)
			return ;
		i++;
	}
}
