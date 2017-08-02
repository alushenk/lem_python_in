//
// Created by lush on 7/31/17.
//

#include "lem-in.h"

t_elem	*create_element()
{
	t_elem *result;

	result = (t_elem*)malloc(sizeof(t_elem));
	result->room = NULL;
	result->next = NULL;
	return (result);
}

size_t	get_length(t_elem *list)
{
	size_t i;

	i = 0;
	while(list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_path	*create_path()
{
	t_path *result;

	result = (t_path*)malloc(sizeof(t_path));
	result->list = NULL;
	result->weight = 0;
	result->ants_count = 0;
	result->next = NULL;
	return (result);
}

void	add_to_path(t_path *path, t_room *room)
{
	t_elem	*new_elem;
	t_elem	*list;

	new_elem = create_element();
	new_elem->room = room;
	list = path->list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new_elem;
	}
	else
		path->list = new_elem;
	path->weight += 1;
}

t_path	*copy_path(t_path *path)
{
	t_path	*result;
	t_elem	*elem;

	result = create_path();
	if (path == NULL)
		return (result);
	elem = path->list;
	while(elem)
	{
		add_to_path(result, elem->room);
		elem = elem->next;
	}
	return (result);
}

t_group	*create_group()
{
	t_group *group;

	group = (t_group*)malloc(sizeof(t_group));
	group->paths = NULL;
	group->efficiency = 0;
	group->number_of_paths = 0;
	group->next = NULL;

	return (group);
}

void	add_path(t_group *group, t_path *path)
{
	t_path	*new_path;

	new_path = create_path();
	new_path->weight = path->weight;
	new_path->list = path->list;
	group->number_of_paths += 1;

	if (group->paths != NULL)
		new_path->next = group->paths;
	group->paths = new_path;
}

t_step	*create_step()
{
	t_step	*result;

	result = (t_step*)malloc(sizeof(t_step));
	result->move = NULL;
	result->next = NULL;
	return (result);
}

void	add_step(t_path *path, t_step *step)
{
	t_step	*elem;

	elem = path->steps;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = step;
	}
	else
		path->steps = step;
}

void	append_step(t_step	**list, t_step *step)
{
	t_step	*elem;

	elem = *list;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = step;
	}
	else
		*list = step;
}

t_move	*create_move(int ant, char *room)
{
	t_move *result;

	result = (t_move*)malloc(sizeof(t_move));
	result->ant = ant;
	result->room = room;
	result->next = NULL;
	return (result);
}

void	add_move(t_step *step, t_move *move)
{
	t_move	*elem;

	if (step->move == NULL)
	{
		step->move = move;
		return ;
	}
	elem = step->move;
	while(elem->next)
		elem = elem->next;
	elem->next = move;
}