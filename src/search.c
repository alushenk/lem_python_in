//
// Created by lush on 7/31/17.
//

#include "lem-in.h"

t_path	*copy_path(t_path *path)
{
	t_path	*result;
	t_elem	*elem;

	result = create_path();
	elem = path->list;
	while(elem)
	{
		add_to_path(result, elem->room);
		elem = elem->next;
	}
	return (result);
}

t_path	*find_all_paths(t_room *start, t_room *end, t_path *path)
{
	t_elem	*elem;
	t_path	*paths;
	t_path	*new_paths;
	t_path	*temp;

	path = copy_path(path);
	add_to_path(path, start);
	if (start == end)
		return (path);
	elem = start->list;
	paths = NULL;
	while (elem)
	{
		if (find_by_id(path->list, elem->room) == NULL)
		{
			new_paths = find_all_paths(elem->room, end, path);
			temp = paths;
			if (paths != NULL)
			{
				while(temp->next)
					temp = temp->next;
				temp->next = new_paths;
			}
			else
				paths = new_paths;

		}
		elem = elem->next;
	}
	return (paths);
}

void	get_all_paths(t_graph *graph)
{
	t_path	*paths;
	t_path	*path;

	path = create_path();
	paths = find_all_paths(graph->start_room, graph->end_room, path);

	graph->paths = paths;
}

