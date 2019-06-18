/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:06:15 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 03:06:17 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** modular multithread functions
** ft_multi_thread parameters : struct with winwidth and range points to
** split image buffer.
** f function is the one handeling calculations.
*/

static void	ft_handle_threads(t_data *multi, int n_threads, int step,
														void *(*f)(void *))
{
	pthread_t	thread_ids[n_threads];
	int			i;

	i = -1;
	while (++i < n_threads)
	{
		multi[i].thread_range.start.x = 0;
		multi[i].thread_range.start.y = step * i;
		multi[i].thread_range.end.x = multi[i].winwidth;
		multi[i].thread_range.end.y = step * (i + 1);
	}
	i = -1;
	while (++i < n_threads)
		pthread_create(&thread_ids[i], NULL, f, (void *)&multi[i]);
	i = -1;
	while (++i < n_threads)
		pthread_join(thread_ids[i], NULL);
}

void		ft_multi_thread(t_data *data, int n_threads, void *(*f)(void *))
{
	t_data	*multi;
	int		i;
	int		step;

	multi = (t_data *)malloc(sizeof(t_data) * n_threads);
	step = data->winwidth / n_threads;
	i = -1;
	while (++i < n_threads)
		multi[i] = *data;
	ft_handle_threads(multi, n_threads, step, f);
	free(multi);
}
