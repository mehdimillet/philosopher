/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 11:52:09 by memillet          #+#    #+#             */
/*   Updated: 2026/03/11 15:13:01 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	printf("%2lld Philo%d is sleeping\n",get_time() ,philo->id);
	pthread_mutex_unlock(&philo->info->mutex);
	usleep(philo->info->t_sleep * 1000);
	return (true);
}