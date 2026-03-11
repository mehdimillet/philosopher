/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:49:24 by memillet          #+#    #+#             */
/*   Updated: 2026/03/11 15:33:32 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo, int i)
{
	if (i == 0)
	{
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		printf("%2lld Philo%d has taken a fork\n",get_time() ,philo->id);
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		printf("%2lld Philo%d has taken a fork\n",get_time() ,philo->id);
	}
	if (i == 1)
	{
		pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
		printf("%2lld Philo%d has taken a fork\n",get_time() ,philo->id);
		pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
		printf("%2lld Philo%d has taken a fork\n",get_time() ,philo->id);		
	}
}

bool	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	pthread_mutex_unlock(&philo->info->mutex);
	if (philo->id % 2 == 0)
		take_fork(philo, 0);
	else
		take_fork(philo, 1);
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	pthread_mutex_lock(&philo->mutex);
	printf("%2lld Philo%d is eating\n",get_time(), philo->id);
	philo->n_eat += 1;
	printf("n_eat = %d\n", philo->n_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->info->t_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	return (true);
}
