/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/26 14:32:26 by vtenneke      #+#    #+#                 */
/*   Updated: 2020/11/26 14:32:26 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <string.h>
#include <unistd.h>

void error(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(data);
	system("leaks philo_three");
	exit(1);
}

int main(int ac, char **av)
{
	t_data	*data;
	char	*id;
	int i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		error(data, E_MALLOC "data");
	memset(data, 0, sizeof(t_data));
	parse_input(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->phil_count);
	if (!data->philos)
		error(data, E_MALLOC "philosophers");
	while (i < data->phil_count)
	{
		id = ultoa(i);
		data->philos[i].eat_lock = init_sem(data, id, 1);
		init_philo(data, &data->philos[i], i, id);
		free(id);
		i++;
	}
	start_processes(data);
	return (0);
}
