//
// Created by lush on 8/1/17.
//

#include "lem-in.h"

t_group	*create_group()
{
	t_group *group;

	group = (t_group*)malloc(sizeof(t_group));
	group->paths = NULL;
	group->length = 0;
	group->next = NULL;

	return (group);
}

void	add_path(t_group *group, t_path *path)
{
	t_path	*new_path;

	new_path = create_path();
	new_path->length = path->length;
	new_path->list = path->list;

	if (group->paths != NULL)
		new_path->next = group->paths;
	group->paths = new_path;
}

int 	overlaps(t_path *a, t_path *b)
{
	t_elem	*temp_a;
	t_elem	*temp_b;

	if (a->length == 2 || b->length == 2)
		return (0);
	temp_a = a->list->next;
	while(temp_a->next)
	{
		temp_b = b->list->next;
		while(temp_b->next)
		{
			if (temp_a->room == temp_b->room)
				return (1);
			temp_b = temp_b->next;
		}
		temp_a = temp_a->next;
	}
	return (0);
}

void	find_path_groups(t_graph *graph)
{
	t_group	*resulting_groups;
	t_group	*group;
	t_path	*a;
	t_path	*b;
	t_path	*c;
	int 	not_overlaps;

	resulting_groups = NULL;
	a = graph->paths;
	while(a)
	{
		group = create_group();
		add_path(group, a);
		b = graph->paths;
		while(b)
		{
			if (a != b)
			{
				c = group->paths;
				not_overlaps = 1;
				while(c)
				{
					if (overlaps(b, c))
					{
						not_overlaps = 0;
						break ;
					}
					c = c->next;
				}
				if (not_overlaps)
					add_path(group, b);
			}
			b = b->next;
		}
		if (resulting_groups != NULL)
			group->next = resulting_groups;
		resulting_groups = group;
		a = a->next;
	}
	graph->groups = resulting_groups;
}