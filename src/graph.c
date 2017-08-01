//
// Created by lush on 7/30/17.
//

#include "lem-in.h"

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

t_graph *create_graph()
{
	t_graph *result;

	result = (t_graph*)malloc(sizeof(t_graph));
	result->number_of_ants = 0;
	result->start_room = NULL;
	result->end_room = NULL;
	result->list = NULL;
	result->paths = NULL;
	result->groups = NULL;
	result->chosen_group = NULL;
	return (result);
}

t_room	*add_room(t_graph *graph, char *str)
{
	t_room	*room;
	t_elem	*elem;
	char	*name;
	char	*x;
	char 	*y;

	name = ft_strsep(&str, ' ');
	if (find_by_name(graph->list, name))
		error("Error! duplicate room name found\n");
	x = ft_strsep(&str, ' ');
	y = ft_strsep(&str, ' ');
	room = create_room(name, err_atoi(x), err_atoi(y));
	free(x);
	free(y);
	elem = create_element();
	elem->room = room;
	if (graph->list != NULL)
		elem->next = graph->list;
	graph->list = elem;
	return (room);
}

void	add_start(t_graph *graph, char *str)
{
	graph->start_room = add_room(graph, str);
}

void	add_end(t_graph *graph, char *str)
{
	graph->end_room = add_room(graph, str);
}

void	add_line(t_graph *graph, char *str)
{
	char	*name_a;
	char	*name_b;
	t_room	*room_a;
	t_room	*room_b;

	name_a = ft_strsep(&str, '-');
	name_b = ft_strsep(&str, '-');
	room_a = find_by_name(graph->list, name_a);
	room_b = find_by_name(graph->list, name_b);
	if (room_a == NULL || room_b == NULL)
		error("Error! linking non-existent rooms\n");
	connect(room_a, room_b);
	if (name_a)
		free(name_a);
	if (name_b)
		free(name_b);
}