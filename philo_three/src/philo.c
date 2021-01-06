/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/27 14:39:26 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/27 14:39:26 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>

static int	reaper(t_philo *philo, unsigned int res)
{
	if (res > philo->data->time.die)
	{
		message(philo->data, philo->id, PHILO_DEAD, false);
		sem_post(philo->data->halt);
		return (1);
	}
	return (0);
}

static void	*manager(void *arg)
{
	t_philo			*philo;
	unsigned int	res;

	philo = arg;
	while(1)
	{
		sem_wait(philo->eat_lock);
		if (!philo->reached && philo->data->min_eat && philo->meals >= philo->data->min_eat)
		{
			sem_post(philo->mealsreached);
			philo->reached = 1;
		}
		res = curr_time(philo->data) - philo->last_eat;
		if (reaper(philo, res))
			exit(0);
		sem_post(philo->eat_lock);
		usleep(500);
	}
	return (NULL);
}

static void		take_forks(t_philo *philo, sem_t *forks)
{
	sem_wait(forks);
	message(philo->data, philo->id, PHILO_FORK, true);
	sem_wait(forks);
	message(philo->data, philo->id, PHILO_EAT, true);
	sem_wait(philo->eat_lock);
	philo->meals++;
	philo->last_eat = curr_time(philo->data);
	sem_post(philo->eat_lock);
}

static void		drop_forks(sem_t *forks)
{
	sem_post(forks);
	sem_post(forks);
}

void 			simulate(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, manager, philo);
	pthread_detach(thread);
	while (1)
	{
		message(philo->data, philo->id, PHILO_THINK, true);
		take_forks(philo, philo->data->forks);
		usleep(philo->data->time.eat * 1000);
		drop_forks(philo->data->forks);
		message(philo->data, philo->id, PHILO_SLEEP, true);
		usleep(philo->data->time.sleep * 1000);
	}
	exit(0);
}