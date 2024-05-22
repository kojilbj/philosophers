/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:16 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:08:31 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_passed_time(size_t time_start)
{
	return (get_now_time() - time_start);
}

size_t	get_now_time(void)
{
	struct timeval		tp;
	size_t				milliseconds;

	milliseconds = 0;
	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

size_t	check_dead(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->time_last_eat_lock);
	if (get_passed_time(philo->time_last_eat) > philo->constraints.time_to_die)
		ret = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(&philo->time_last_eat_lock);
	return (ret);
}
