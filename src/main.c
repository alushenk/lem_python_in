/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:23:51 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:23:52 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(int argc, char **argv)
{
	t_graph	*graph;
	int		fd;

	graph = create_graph();
	fd = 0;
	if (argc == 3 && ft_strcmp(argv[1], "-s") == 0)
	{
		if ((fd = open(argv[2], O_RDONLY)) == -1)
			error("Error! can't open file\n", graph);
	}
	parse(graph, fd);
	if (fd != 0)
		close(fd);
	find_path_groups(graph);
	choose_path_group(graph);
	generate_steps(graph);
	display_lines(graph->lines);
	display_steps(graph->steps);
	free_graph(graph);
	return (0);
}
