/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_two.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vtenneke <vtenneke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/07 14:03:57 by vtenneke      #+#    #+#                 */
/*   Updated: 2021/01/07 14:03:57 by vtenneke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_three.h>

sem_t	*init_sem(t_data *data, char *name, int val)
{
	sem_t *res;

	sem_unlink(name);
	res = sem_open(name, O_CREAT, 666, val);
	if (!res)
		error(data, E_SEMAPH);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	k;

	k = 0;
	if (s1 == 0)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	dest = (char*)malloc(i + 1);
	if (!(dest))
		return (NULL);
	while (*s1)
	{
		dest[k] = *s1;
		s1++;
		k++;
	}
	while (*s2)
	{
		dest[k] = *s2;
		s2++;
		k++;
	}
	dest[k] = '\0';
	return (dest);
}

int		ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = *str == '-' ? -1 : 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * (int)res);
}
