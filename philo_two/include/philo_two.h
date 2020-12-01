/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 14:43:53 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/26 14:43:53 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define E_MALLOC		"Failed to allocate memory for: "
# define E_THREAD		"Failed to create thread"
# define E_INPUT		"Invalid input found"
# define E_ARGC			"Invalid amount of arguments"

# define PHILO_THINK	" is thinking\n"
# define PHILO_FORK		" has taken a fork\n"
# define PHILO_EAT		" is eating\n"
# define PHILO_SLEEP	" is sleeping\n"
# define PHILO_DEAD		" died\n"

# include <semaphore.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pthread.h>

enum				e_fork
{
	LEFT,
	RIGHT,
};

typedef struct		s_time
{
	unsigned int	die;
	unsigned int	sleep;
	unsigned int	eat;
}					t_time;

typedef struct s_data			t_data;

typedef struct 		s_philo
{
	int				id;
	int				meals;
	size_t			last_eat;
	t_data			*data;
	sem_t			*eat_lock;
}					t_philo;

typedef struct		s_data
{
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*write_lock;
	size_t			start_time;
	int				phil_count;
	t_time			time;
	int				min_eat;
	bool			should_eat;
}					t_data;

/*
**	Parser
*/
void				init_philo(t_data *data, t_philo *philo, int id);
void				parse_input(t_data *data, int ac, char **av);

/*
**	Philosophers
*/
void 				*simulate(void *arg);
void				init_philo(t_data *data, t_philo *philo, int id);

/*
**	Threads
*/
int 				start_threads(t_data *data);

/*
**	Time
*/
unsigned long 		get_time();
unsigned long 		curr_time(t_data *data);

/*
**	Utilities
*/
int					ft_atoi(const char *str);
int					ft_putstr_fd(char *str, int fd);
void				error(t_data *data, char *msg);
bool				is_number(char *str);
void 				message(t_data *data, int id, char *msg, bool unlock);
char				*ultoa(unsigned long number);

#endif