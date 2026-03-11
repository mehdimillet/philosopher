/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:44:18 by memillet          #+#    #+#             */
/*   Updated: 2026/03/11 15:12:55 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	printf("%2lld Philo%d is thinking\n",get_time(), philo->id);
	pthread_mutex_unlock(&philo->info->mutex);
	return (true);
}