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

#include "philo_two.h"
#include <unistd.h>

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

void			*simulate(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		message(philo->data, philo->id, PHILO_THINK, true);
		take_forks(philo, philo->data->forks);
		usleep(philo->data->time.eat * 1000);
		drop_forks(philo->data->forks);
		message(philo->data, philo->id, PHILO_SLEEP, true);
		usleep(philo->data->time.sleep * 1000);
	}
	return (NULL);
}
