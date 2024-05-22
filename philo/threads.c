/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:46 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:05:48 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	switch_dead_fg(t_philo *philo)
{
	while (is_dead(philo) == FALSE)
	{
		pthread_mutex_lock(&philo->dead_fg_lock);
		philo->dead_fg = TRUE;
		pthread_mutex_unlock(&philo->dead_fg_lock);
		philo_put_down_forks(philo);
		philo = philo->next;
	}
}

void	*observer(void *data)
{
	t_philo	*philo;
	size_t	count;

	philo = (t_philo *)data;
	count = 0;
	while (1)
	{
		if (has_eaten_enough(philo) == TRUE)
			count++;
		else
			count = 0;
		if (count == philo->constraints.number_of_philos
			|| check_dead(philo) == TRUE)
		{
			if (count != philo->constraints.number_of_philos)
				put_dead_log(philo);
			switch_dead_fg(philo);
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}

void	*philo_life_circle(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (is_dead(philo) == FALSE)
	{
		philo_eat(philo, philo->constraints.time_to_eat);
		philo_sleep(philo, philo->constraints.time_to_sleep);
		philo_think(philo);
	}
	return (NULL);
}

int	philos_create(t_philo *philos)
{
	int	i;
	int	ret;

	i = 0;
	while (i < philos->constraints.number_of_philos)
	{
		ret = pthread_create(&(philos->thread_id),
				NULL, philo_life_circle, (void *)philos);
		philos = philos->next;
		i++;
	}
	return (ret);
}
