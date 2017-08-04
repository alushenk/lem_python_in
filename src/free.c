/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:09 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:10 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_list(t_elem *list)
{
	t_elem *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}

void	free_paths(t_path *path)
{
	t_path *temp;

	while (path)
	{
		temp = path;
		path = path->next;
		free_list(temp->list);
		free(temp);
	}
}

void	free_groups(t_group *group)
{
	t_group *temp;
	t_path	*path;
	int		count;

	while (group)
	{
		temp = group;
		group = group->next;
		count = temp->number_of_paths;
		while (count > 0)
		{
			path = temp->paths;
			temp->paths = temp->paths->next;
			free(path);
			count--;
		}
		free(temp);
	}
}

void	free_steps(t_step *step)
{
	t_step	*temp;
	t_move	*move;

	while (step)
	{
		temp = step;
		step = step->next;
		while (temp->move)
		{
			move = temp->move;
			temp->move = temp->move->next;
			free(move);
		}
		free(temp);
	}
}

void	free_rooms(t_elem *elem)
{
	t_elem *temp;

	while (elem)
	{
		temp = elem;
		elem = elem->next;
		free(temp->room->name);
		free_list(temp->room->list);
		free(temp->room);
		free(temp);
	}
}

void	free_graph(t_graph *graph)
{
	free_paths(graph->paths);
	free_groups(graph->groups);
	free_steps(graph->steps);
	free_rooms(graph->list);
	free(graph);
}
