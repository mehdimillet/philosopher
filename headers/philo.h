#pragma once

/* ======================= */
/*        INCLUDES         */
/* ======================= */

# include <stdio.h> //printf,
# include <pthread.h> //pthread, muthex
# include <stdlib.h> //malloc, free, 
# include <unistd.h> //write, usleep
# include <sys/time.h> // get_time_of_day
# include <stdbool.h> // for true and false
# include <limits.h> // for INT_MAX
# include <string.h>
# include <aio.h> //for size_t

/* ======================= */
/*       	STRUCT         */
/* ======================= */

typedef struct s_philo t_philo; //forward declaration (to tell to the compiler t_philo exists)

typedef struct	s_data
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
long		ft_atol(const char *nptr);
long long	get_time();

/* ======================= */
/*        PARSING.C        */
/* ======================= */

int		parsing(t_data *args, int ac, char **av);
void	init_struct(t_data *set, int ac, char **av);
int		check_params(t_data *args);
void	init_data(t_data *data);

/* ======================= */
/*        THREAD.C         */
/* ======================= */

void	thread(t_data *data);
void	*monitor_routine(void *arg);
void	*routine(void *arg);
bool    ft_eat(t_philo *philo);
bool	ft_sleep(t_philo *philo);
bool	ft_think(t_philo *philo);

/* ======================= */
/*      	PHILO.C        */
/* ======================= */

int		main(int ac, char **av);
