/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:02:54 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/22 13:14:37 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <libft.h>

# define TRUE	1
# define FALSE	0

typedef struct s_constraints
{
	size_t	number_of_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_each_philos_must_eat;
}	t_constraints;

typedef struct s_philo
{
	size_t	num;
	size_t	time_start;
	size_t	time_last_eat;
	size_t	eat_count;
	int	dead_fg;
	struct s_philo	*next;
	struct s_constraints	constraints;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*output_lock;
	pthread_mutex_t	dead_fg_lock;
	pthread_mutex_t	time_last_eat_lock;
	pthread_mutex_t	eat_count_lock;
	pthread_t	thread_id;
}	t_philo;

//initialize_functions
void	constraints_init(t_constraints *constraints, char *av[]);
t_philo	*seating_philos(t_constraints constraints);

//thread_functions
void	*observer(void *data);
int	philos_create(t_philo *philos);
void	*philo_life_circle(void *data);
int	philo_sleep(t_philo *philo, int time_sleep);
int	philo_eat(t_philo *philo, int time_eat);
int	philo_think(t_philo *philo);
int	philo_put_down_forks(t_philo *philo);

//write_functions
int	put_timestamp(size_t time_start);
int	put_log(t_philo *philo, char *str);
int	put_fork_log(t_philo *philo);
int	put_dead_log(t_philo *philo);

//validate_functions
int	validate(char *args[]);

//get_time_functions
size_t	get_passed_time(size_t time_start);
size_t	get_now_time(void);

//check_functions
size_t	check_dead(t_philo *philo);
int	is_dead(t_philo *philo);
int	has_eaten_enough(t_philo *philo);
void	plus_eat_count(t_philo *philo);

#endif
