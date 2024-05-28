/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:31 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/24 10:41:57 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_take_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(&philo->right_fork);
	put_fork_log(philo);
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	put_fork_log(philo);
	return (0);
}

int	philo_put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	philo_sleep(t_philo *philo, int time_sleep)
{
	put_log(philo, "sleeping");
	if (is_dead(philo) == FALSE)
			philo_usleep(time_sleep);
	return (0);
}

int	philo_eat(t_philo *philo, int time_eat)
{
	if (is_dead(philo) == FALSE)
		philo_take_fork(philo);
	pthread_mutex_lock(&philo->time_last_eat_lock);
	philo->time_last_eat = get_now_time();
	pthread_mutex_unlock(&philo->time_last_eat_lock);
	put_log(philo, "eating");
	if (is_dead(philo) == FALSE)
		philo_usleep(time_eat);
	philo_put_down_forks(philo);
	plus_eat_count(philo);
	return (0);
}

int	philo_think(t_philo *philo)
{
	put_log(philo, "thinking");
	//usleep(100);
	return (0);
}
