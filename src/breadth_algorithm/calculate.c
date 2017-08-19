/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:42:28 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/19 14:42:29 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	calculate_step(t_room *room, t_path *queue)
{
	t_elem	*list;

	list = room->list;
	while (list)
	{
		if (list->room->dist > room->dist + 1)
		{
			list->room->dist = room->dist + 1;
			add_to_path(queue, list->room);
		}
		list = list->next;
	}
}

void	calculate_graph(t_room *room)
{
	t_path	*queue;
	t_elem	*step;
	t_path	*new_queue;

	queue = create_path();
	room->dist = 0;
	calculate_step(room, queue);
	while (queue->list)
	{
		step = queue->list;
		new_queue = create_path();
		while (step)
		{
			calculate_step(step->room, new_queue);
			step = step->next;
		}
		free_paths(queue);
		queue = new_queue;
	}
	free_paths(queue);
}
