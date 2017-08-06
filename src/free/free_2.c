/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 15:52:03 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/06 15:52:04 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	free_rooms(t_elem *list)
{
	t_elem *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->room->name);
		free_list(temp->room->list);
		free(temp->room);
		free(temp);
	}
}

void	free_lines(t_line *line)
{
	t_line *temp;

	while (line)
	{
		temp = line;
		line = line->next;
		free(temp->name);
		free(temp);
	}
}
