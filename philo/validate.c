/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:03:54 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:26:52 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_invalid_char(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (1);
	while (arg[i] != '\0')
	{
		if (!('0' <= arg[i] && arg[i] <= '9'))
			return (-1);
		i++;
	}
	return (1);
}

int	validate(char *args[])
{
	if (check_invalid_char(args[0]) == -1)
		printf("number_of_philosophers is invalid.\n");
	else if (check_invalid_char(args[1]) == -1)
		printf("time_to_eat is invalid.\n");
	else if (check_invalid_char(args[3]) == -1)
		printf("time_to_sleep is invalid.\n");
	else if (args[4] != NULL && check_invalid_char(args[4]) == -1)
		printf("number_of_times_each_philosopher_must_eat is invalid.\n");
	else if (args[4] != NULL && ft_atoi(args[4]) == 0)
		printf("number_of_times_each_philosopher_must_eat is invalid.\n");
	else
		return (1);
	return (-1);
}
