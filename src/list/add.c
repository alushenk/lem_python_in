/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 11:10:05 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 11:10:07 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

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

void	append_step(t_step **list, t_step *step)
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

void	add_move(t_step *step, t_move *move)
{
	t_move	*elem;

	if (step->move == NULL)
	{
		step->move = move;
		return ;
	}
	elem = step->move;
	while (elem->next)
		elem = elem->next;
	elem->next = move;
}
