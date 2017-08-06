/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 16:42:43 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/06 16:42:44 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	error_parse(t_graph *graph, char *str, char **x, char **y)
{
	if (*str == '\0')
		error("Error! wrong coordinates\n", graph);
	*x = ft_strsep(&str, ' ');
	if (*str == '\0')
		error("Error! wrong coordinates\n", graph);
	*y = ft_strsep(&str, ' ');
	if (*str != '\0')
		error("Error! wrong coordinates\n", graph);
}

t_room	*add_room(t_graph *graph, char *str)
{
	t_room	*room;
	t_elem	*elem;
	char	*name;
	char	*x;
	char	*y;

	name = ft_strsep(&str, ' ');
	if (find_by_name(graph->list, name))
		error("Error! duplicate room name found\n", graph);
	error_parse(graph, str, &x, &y);
	room = create_room(name, err_atoi(x, graph), err_atoi(y, graph));
	free(x);
	free(y);
	elem = create_element();
	elem->room = room;
	if (graph->list != NULL)
		elem->next = graph->list;
	graph->list = elem;
	return (room);
}
