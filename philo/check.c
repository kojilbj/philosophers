/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:51:02 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/28 09:40:26 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	has_eaten_enough(t_philo *philo)
{
	int	ret;

	if (philo->rules.times_each_philos_must_eat == 0)
		return (FALSE);
	pthread_mutex_lock(&philo->eat_count_lock);
	if (philo->eat_count >= philo->rules.times_each_philos_must_eat)
		ret = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (ret);
}

int	is_dead(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->dead_fg_lock);
	if (philo->dead_fg == TRUE)
		ret = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(&philo->dead_fg_lock);
	return (ret);
}

void	plus_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_count_lock);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_lock);
}
