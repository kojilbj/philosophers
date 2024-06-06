/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:46:53 by kojwatan          #+#    #+#             */
/*   Updated: 2024/06/06 17:06:45 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pthread_join_philos(t_philo *philos)
{
	int				i;
	pthread_mutex_t	*output;
	t_philo			*tmp;

	i = 0;
	output = philos->output_lock;
	while (i < philos->rules.number_of_philos)
	{
		tmp = philos;
		pthread_join(tmp->thread_id, NULL);
		pthread_mutex_destroy(&tmp->right_fork);
		pthread_mutex_destroy(&tmp->dead_fg_lock);
		pthread_mutex_destroy(&tmp->time_last_eat_lock);
		pthread_mutex_destroy(&tmp->eat_count_lock);
		i++;
		philos = philos->next;
		free(tmp);
	}
	pthread_mutex_destroy(output);
	free(output);
}

int	main(int ac, char *av[])
{
	t_rules			rules;
	t_philo			*philos;
	pthread_t		threadob;

	if (ac < 5 || validate(&av[1]) == -1)
		return (1);
	rules_init(&rules, &av[1]);
	philos = seating_philos(rules);
	if (philos == NULL)
		return (1);
	pthread_create(&threadob, NULL, observer, (void *)philos);
	philos_create(philos);
	pthread_join(threadob, NULL);
	pthread_join_philos(philos);
	return (0);
}
