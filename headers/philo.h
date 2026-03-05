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
# include <limits.h> // for LONG_MAX

/* ======================= */
/*       	STRUCT         */
/* ======================= */

typedef struct s_philo t_philo; //forward declaration (for said to the compiler t_philo exists)

typedef struct	s_data
{
	int				nb_philo;
	int				nb_eat;
	int				dead;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	long long		t_start;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			n_eat;
	int			l_fork;
	int			r_fork;
	long long	last_eat;
	t_data		*info;
}	t_philo;

typedef struct s_time
{
	time_t		t_sec;
	suseconds_t	t_usec;
}	t_time;

/* ======================= */
/*      	UTILS.C        */
/* ======================= */

long	ft_atol(const char *nptr);
int		ft_isdigit(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* ======================= */
/*        PARSING.C        */
/* ======================= */

void	init_struct(t_data *set, int ac, char **av);
int		parsing(t_data *args, int ac, char **av);
int		check_params(t_data *args);

/* ======================= */
/*      	PHILO.C        */
/* ======================= */

int		main(int ac, char **av);
