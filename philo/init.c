/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:07 by kojwatan          #+#    #+#             */
/*   Updated: 2024/06/06 16:37:51 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_strtol(const char *str, int sign)
{
	long	result;
	long	tmp;

	result = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + *str - '0';
		if (result < tmp)
		{
			if (sign == -1)
				return (LONG_MIN);
			else
				return (LONG_MAX);
		}
		str++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		sign_fg;

	sign_fg = 0;
	result = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		if (sign_fg == 1)
			return (result);
		sign_fg = 1;
		str++;
	}
	return ((int)(ft_strtol(str, sign)));
}

void	rules_init(t_rules *rules, char *av[])
{
	rules->number_of_philos = ft_atoi(av[0]);
	rules->time_to_die = ft_atoi(av[1]);
	rules->time_to_eat = ft_atoi(av[2]);
	rules->time_to_sleep = ft_atoi(av[3]);
	if (av[4] != NULL)
		rules->times_each_philos_must_eat = ft_atoi(av[4]);
	else
		rules->times_each_philos_must_eat = -1;
}

int	mutexes_init(t_philo *philo)
{
	if (pthread_mutex_init(&philo->right_fork, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&philo->dead_fg_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->right_fork);
		return (-1);
	}
	if (pthread_mutex_init(&philo->time_last_eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->right_fork);
		pthread_mutex_destroy(&philo->dead_fg_lock);
		return (-1);
	}
	if (pthread_mutex_init(&philo->eat_count_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->right_fork);
		pthread_mutex_destroy(&philo->dead_fg_lock);
		pthread_mutex_destroy(&philo->time_last_eat_lock);
		return (-1);
	}
	return (0);
}
