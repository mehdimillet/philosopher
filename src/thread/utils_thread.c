/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:24:47 by memillet          #+#    #+#             */
/*   Updated: 2026/03/19 10:47:33 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_is_full(t_data *data)
{
	pthread_mutex_lock(&data->mutex);
	data->dead = 1;
	pthread_mutex_unlock(&data->mutex);
}

void	ft_is_dead(t_data *data, int i)
{
	data->dead = 1;
	printf("%2lld Philo%d is dead\n",
		(get_time() - data->t_start), data->philo[i].id);
	pthread_mutex_unlock(&data->mutex);
}

void	ft_have_tmp(t_philo *philo, long long *tmp, int *n_eat)
{
	pthread_mutex_lock(&philo->mutex);
	*tmp = get_time() - philo->last_eat;
	*n_eat = philo->n_eat;
	pthread_mutex_unlock(&philo->mutex);
}
