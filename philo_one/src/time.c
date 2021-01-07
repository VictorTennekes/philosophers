/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 16:12:25 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/26 16:12:25 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	res;

	gettimeofday(&time, 0);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}

unsigned long	curr_time(t_data *data)
{
	return (get_time() - data->start_time);
}
