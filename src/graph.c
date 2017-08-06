/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:31 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:32 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_strsep(char **str, char sep)
{
	int		i;
	char	*result;

	i = 0;
	while (**str == sep && **str != '\0')
		(*str)++;
	while ((*str)[i] != sep && (*str)[i] != '\0')
		i++;
	if (i == 0)
		return (NULL);
	result = ft_strnew(i);
	ft_strncpy(result, *str, i);
	while ((i-- > 0 || **str == sep) && **str != '\0')
		(*str)++;
	return (result);
}

t_graph	*create_graph(void)
{
	t_graph *result;

	result = (t_graph*)malloc(sizeof(t_graph));
	result->number_of_ants = 0;
	result->start_room = NULL;
	result->end_room = NULL;
	result->list = NULL;
	result->lines = NULL;
	result->paths = NULL;
	result->groups = NULL;
	result->chosen_group = NULL;
	result->steps = NULL;
	return (result);
}

t_line	*create_line(char *str)
{
	t_line *result;

	result = (t_line*)malloc(sizeof(t_line));
	result->name = ft_strdup(str);
	result->next = NULL;
	return (result);
}

void	add_line(t_graph *graph, char *str)
{
	char	*name_a;
	char	*name_b;
	t_room	*room_a;
	t_room	*room_b;
	t_line	*line;

	line = create_line(str);
	if (graph->lines != NULL)
		line->next = graph->lines;
	graph->lines = line;
	name_a = ft_strsep(&str, '-');
	name_b = ft_strsep(&str, '-');
	room_a = find_by_name(graph->list, name_a);
	room_b = find_by_name(graph->list, name_b);
	if (room_a == NULL || room_b == NULL)
		error("Error! linking non-existent rooms\n", graph);
	connect(room_a, room_b, graph);
	if (name_a)
		free(name_a);
	if (name_b)
		free(name_b);
}
