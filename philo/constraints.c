/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:07 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:09:13 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	constraints_init(t_constraints *constraints, char *av[])
{
	constraints->number_of_philos = atoi(av[0]);
	constraints->time_to_die = atoi(av[1]);
	constraints->time_to_eat = atoi(av[2]);
	constraints->time_to_sleep = atoi(av[3]);
	if (av[4] != NULL)
		constraints->times_each_philos_must_eat = atoi(av[4]);
	else
		constraints->times_each_philos_must_eat = 0;
}
