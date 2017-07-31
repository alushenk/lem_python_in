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
			error("Error! can't open file");
	}
	parse(graph, fd);
	if (fd != 0)
		close(fd);

	get_all_paths(graph);


	return (0);
}