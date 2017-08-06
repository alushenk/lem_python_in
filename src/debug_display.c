/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 14:52:05 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/06 14:52:06 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	display_path(t_path *path)
{
	t_elem *elem;

	elem = path->list;
	ft_putstr("( ");
	while (elem)
	{
		ft_putstr(elem->room->name);
		ft_putstr(", ");
		elem = elem->next;
	}
	ft_putstr(")\n");
}

void	display_paths(t_path *path)
{
	while (path)
	{
		display_path(path);
		path = path->next;
	}
}

void	display_groups(t_group *group)
{
	while (group)
	{
		display_paths(group->paths);
		ft_putchar('\n');
		group = group->next;
	}
}
