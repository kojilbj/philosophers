/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 10:37:58 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/24 10:43:47 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_usleep(size_t time_sleep)
{
	size_t	start_time;

	start_time = get_now_time();
	while (get_now_time() - start_time < time_sleep)
		usleep(100);
	return (0);
}
