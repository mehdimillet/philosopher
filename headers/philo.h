/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memillet <memillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 10:56:30 by memillet          #+#    #+#             */
/*   Updated: 2026/03/19 11:24:16 by memillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* ======================= */
/*        INCLUDES         */
/* ======================= */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <aio.h>

/* ======================= */
/*       	STRUCT         */
/* ======================= */

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					nb_eat;
	int					dead;
	long long			t_die;
	long long			t_eat;
	long long			t_sleep;
	long long			t_start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex;
	pthread_t			monitor;
	t_philo				*philo;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					n_eat;
	int					l_fork;
	int					r_fork;
	long long			last_eat;
	pthread_t			thread_id;
	pthread_mutex_t		mutex;
	t_data				*info;
}	t_philo;

/* ======================= */
/*      	UTILS.C        */
/* ======================= */

int			ft_isdigit(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			check_death(t_philo *philo);
long		ft_atol(const char *nptr);
long long	get_time(void);

/* ======================= */
/*        PARSING.C        */
/* ======================= */

int			parsing(t_data *args, int ac, char **av);
void		init_struct(t_data *set, int ac, char **av);
int			check_params(t_data *args);
bool		init_data(t_data *data);

/* ======================= */
/*        THREAD.C         */
/* ======================= */

void		thread(t_data *data);
void		*monitor_routine(void *arg);
void		*routine(void *arg);
bool		ft_eat(t_philo *philo);
bool		ft_sleep(t_philo *philo);
bool		ft_think(t_philo *philo);
void		better_usleep(long long ms, t_data *data);

/* ======================= */
/*      	PHILO.C        */
/* ======================= */

int			main(int ac, char **av);
void		ft_is_full(t_data *data);
void		ft_is_dead(t_data *data, int i);
void		ft_have_tmp(t_philo *philo, long long *tmp, int *n_eat);
