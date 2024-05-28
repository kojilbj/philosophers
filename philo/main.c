/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: watanabekoji <watanabekoji@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:46:53 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/28 14:24:39 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	pthread_join_philos(t_philo *philos)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < philos->rules.number_of_philos)
	{
		tmp = philos;
		pthread_join(philos->thread_id, NULL);
		pthread_mutex_destroy(&philos->right_fork);
		i++;
		philos = philos->next;
		free(tmp);
	}
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
