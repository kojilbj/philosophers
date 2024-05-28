/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seating_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:38 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/28 09:39:25 by watanabekoj      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*new_philo(int num, t_rules rules,
		size_t time_start, pthread_mutex_t *output_lock)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->num = num;
	new->next = NULL;
	new->dead_fg = FALSE;
	new->time_start = time_start;
	new->time_last_eat = time_start;
	new->rules = rules;
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

void	free_philos(t_philo *philos)
{
	t_philo	*tmp;

	while (philos != NULL)
	{
		tmp = philos;
		philos = philos->next;
		free(tmp);
	}
}

t_philo	*seating_philos_util(t_rules rules, t_philo *top,
		size_t time_start, pthread_mutex_t *output_lock)
{
	t_philo		*new;
	t_philo		*prev;
	size_t		i;

	i = 1;
	prev = top;
	new = top;
	while (i < rules.number_of_philos)
	{
		new = new_philo(i + 1, rules, time_start, output_lock);
		if (new == NULL)
		{
			free_philos(top);
			return (NULL);
		}
		add_philo(new, prev);
		prev = new;
		i++;
	}
	new->next = top;
	top->left_fork = &new->right_fork;
	return (top);
}

t_philo	*seating_philos(t_rules rules)
{
	pthread_mutex_t		output_lock;
	t_philo				*top;

	pthread_mutex_init(&output_lock, NULL);
	top = new_philo(1, rules, get_now_time(), &output_lock);
	if (top == NULL)
		return (NULL);
	top = seating_philos_util(rules, top, get_now_time(), &output_lock);
	return (top);
}
