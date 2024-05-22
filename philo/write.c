/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:04:04 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:07:17 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	put_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->output_lock);
	if (is_dead(philo) == FALSE)
		printf("%lu %zu is %s\n",
			get_passed_time(philo->time_start), philo->num, str);
	pthread_mutex_unlock(philo->output_lock);
	return (0);
}

int	put_fork_log(t_philo *philo)
{
	pthread_mutex_lock(philo->output_lock);
	if (is_dead(philo) == FALSE)
		printf("%lu %zu has taken a fork\n",
			get_passed_time(philo->time_start), philo->num);
	pthread_mutex_unlock(philo->output_lock);
	return (0);
}

int	put_dead_log(t_philo *philo)
{
	pthread_mutex_lock(philo->output_lock);
	printf("%lu %zu died\n", get_passed_time(philo->time_start), philo->num);
	pthread_mutex_unlock(&philo->time_last_eat_lock);
	pthread_mutex_unlock(philo->output_lock);
	return (0);
}
