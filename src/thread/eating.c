/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:49:24 by memillet          #+#    #+#             */
/*   Updated: 2026/03/16 11:46:10 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
	printf("%2lld Philo%d has taken a fork\n", (get_time() - philo->info->t_start) ,philo->id);
	usleep(philo->info->t_die * 1000);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->mutex);
}

static void	take_fork(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->l_fork > philo->r_fork)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(&philo->info->forks[first]);
	if (check_death(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->info->mutex);
	printf("%2lld Philo%d has taken a fork\n",(get_time() - philo->info->t_start) ,philo->id);
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_lock(&philo->info->forks[second]);
	if (check_death(philo) == 1)
		return ;		
	pthread_mutex_lock(&philo->info->mutex);
	printf("%2lld Philo%d has taken a fork\n",(get_time() - philo->info->t_start) ,philo->id);
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_lock(&philo->mutex);
    philo->last_eat = get_time();
    pthread_mutex_unlock(&philo->mutex);
}

static void	if_death(t_philo *philo)
{
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
}

bool	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->nb_philo == 1)
		return (one_philo(philo), false);
	pthread_mutex_unlock(&philo->info->mutex);
	if (check_death(philo) == 1)
		return (if_death(philo), false);
	take_fork(philo);
	pthread_mutex_lock(&philo->info->mutex);
	if (philo->info->dead != 0)
	{
		pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
		return (pthread_mutex_unlock(&philo->info->mutex), false);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	printf("%2lld Philo%d is eating\n",(get_time() - philo->info->t_start), philo->id);
	philo->n_eat += 1;
	pthread_mutex_unlock(&philo->info->mutex);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->info->t_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
	return (true);
}
