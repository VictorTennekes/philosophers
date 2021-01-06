/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 16:35:46 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/30 16:35:46 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <unistd.h>
#include <signal.h>

static void kill_processes(t_data *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->phil_count)
	{
		kill(data->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->phil_count)
	{
		(void)waitpid(data->pids[i], &pid, 0);
		i++;
	}
	exit(0);
}

void *satisfaction_counter(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = arg;
	while (i < data->phil_count)
	{
		sem_wait(data->satisfaction[i]);
		i++;
	}
	sem_post(data->halt);
	return (NULL);
}

void 		start_processes(t_data *data)
{
	int i;
	int	pid;
	pthread_t thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->phil_count)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (!pid)
			simulate(&data->philos[i]);
		data->pids[i] = pid;
		i++;
	}
	pthread_create(&thread, NULL, satisfaction_counter, data);
	pthread_detach(thread);
	sem_wait(data->halt);
	kill_processes(data);
}