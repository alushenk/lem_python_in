//
// Created by lush on 8/1/17.
//

#include "lem-in.h"

void	free_list(t_elem *list)
{
	t_elem *temp;

	while(list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_paths(t_path *path)
{
	t_path *temp;

	while(path)
	{
		temp = path;
		path = path->next;
		free_list(temp->list);
		free(temp);
	}
}

void	free_graph(t_graph *graph)
{
	t_elem *elem;
	t_elem *tmp;

	free_paths(graph->paths);
	elem = graph->list;
	while(elem)
	{
		tmp = elem;
		elem = elem->next;
		free(tmp->room->name);
		free_list(tmp->room->list);
		free(tmp->room);
		free(tmp);
	}
	free(graph);
}