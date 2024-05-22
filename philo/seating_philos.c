/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seating_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:38 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:10:54 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*new_philo(int num, t_constraints constaraints,
		size_t time_start, pthread_mutex_t *output_lock)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	new->num = num;
	new->next = NULL;
	new->dead_fg = FALSE;
	new->time_start = time_start;
	new->time_last_eat = time_start;
	new->constraints = constaraints;
	new->eat_count = 0;
	new->output_lock = output_lock;
	pthread_mutex_init(&new->right_fork, NULL);
	pthread_mutex_init(&new->dead_fg_lock, NULL);
	pthread_mutex_init(&new->time_last_eat_lock, NULL);
	pthread_mutex_init(&new->eat_count_lock, NULL);
	return (new);
}

void	add_philo(t_philo *new, t_philo *prev)
{
	prev->next = new;
	new->left_fork = &(prev->right_fork);
}

t_philo	*seating_philos(t_constraints constraints)
{
	int			i;
	size_t			time_start;
	t_philo			*top;
	t_philo			*new;
	t_philo			*prev;
	pthread_mutex_t		output_lock;

	time_start = get_now_time();
	pthread_mutex_init(&output_lock, NULL);
	i = 1;
	top = new_philo(i, constraints, time_start, &output_lock);
	prev = top;
	new = top;
	while (i < constraints.number_of_philos)
	{
		new = new_philo(i + 1, constraints, time_start, &output_lock);
		add_philo(new, prev);
		prev = new;
		i++;
	}
	new->next = top;
	top->left_fork = &new->right_fork;
	return (top);
}
