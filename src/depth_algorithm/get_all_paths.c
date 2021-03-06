/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:23 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:26 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	find(t_path *path, t_path **paths, t_elem *elem, t_room *end)
{
	t_path	*new_paths;
	t_path	*temp;

	if (find_by_id(path->list, elem->room) == NULL)
	{
		new_paths = find_paths(elem->room, end, path);
		temp = *paths;
		if (*paths != NULL)
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new_paths;
		}
		else
			*paths = new_paths;
	}
}

t_path	*find_paths(t_room *start, t_room *end, t_path *path)
{
	t_elem	*elem;
	t_path	*paths;

	path = copy_path(path);
	add_to_path(path, start);
	if (start == end)
		return (path);
	elem = start->list;
	paths = NULL;
	while (elem)
	{
		find(path, &paths, elem, end);
		elem = elem->next;
	}
	free_list(path->list);
	free(path);
	return (paths);
}

void	get_all_paths(t_graph *graph)
{
	t_path	*paths;

	paths = find_paths(graph->start_room, graph->end_room, NULL);
	graph->paths = paths;
}
