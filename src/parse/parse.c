/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:58 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:59 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	parse_ants(t_graph *graph, int fd, char *line)
{
	get_next_line(fd, &line);
	while (ft_strlen(line) > 0 && line[0] == '#')
	{
		if (ft_strlen(line) > 1 && line[1] == '#')
			error("Error! no commands here\n", graph);
		free(line);
		get_next_line(fd, &line);
	}
	graph->number_of_ants = err_atoi(line, graph);
	free(line);
	if (graph->number_of_ants <= 0)
		error("Error! no ants given\n", graph);
}

void	parse_lines(t_graph *graph, int fd, char *line)
{
	if (graph->list == NULL)
		error("Error! no rooms\n", graph);
	if (graph->start_room == NULL)
		error("Error! no start room\n", graph);
	if (graph->end_room == NULL)
		error("Error! no end room\n", graph);
	while (line || get_next_line(fd, &line) == 1)
	{
		if (line[0] != '#')
			add_line(graph, line);
		free(line);
		line = NULL;
	}
}

void	parse(t_graph *graph, int fd)
{
	char	*line;

	line = NULL;
	parse_ants(graph, fd, line);
	parse_rooms(graph, fd, &line);
	parse_lines(graph, fd, line);
}
