/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:52:09 by memillet          #+#    #+#             */
/*   Updated: 2026/03/19 10:47:18 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	printf("%2lld Philo%d is sleeping\n",
		(get_time() - philo->info->t_start), philo->id);
	pthread_mutex_unlock(&philo->info->mutex);
	better_usleep(philo->info->t_sleep, philo->info);
	return (true);
}

void	better_usleep(long long ms, t_data *data)
{
	long long	start;

	start = get_time();
	while (get_time() - start < ms)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->mutex);
			return ;
		}
		pthread_mutex_unlock(&data->mutex);
		usleep(500);
	}
}
