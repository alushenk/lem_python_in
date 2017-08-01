//
// Created by lush on 7/28/17.
//

#include "lem-in.h"

int main(int argc, char **argv)
{
	t_graph *graph;
	int 	fd;

	graph = create_graph();
	fd = 0;
	if (argc == 3 && ft_strcmp(argv[1], "-s") == 0)
	{
		if ((fd = open(argv[2], O_RDONLY)) == -1)
			error("Error! can't open file\n");
	}
	parse(graph, fd);
	if (fd != 0)
		close(fd);
	get_all_paths(graph);
	display_paths(graph->paths);
	ft_putstr("--------------------------------------------------------------------------------------\n");
	find_path_groups(graph);
	display_groups(graph->groups);
	choose_path_group(graph);
	printf("optimal group: \n");
	display_paths(graph->chosen_group->paths);

	free_graph(graph);
	return (0);
}