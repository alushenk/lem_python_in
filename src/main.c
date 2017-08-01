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

	t_path *path;
	t_path *temp;
	path = graph->paths;
	while(path)
	{
		temp = path;
		path = path->next;
		free_path(&temp);
	}

	t_elem *elem;
	t_elem *tmp;
	elem = graph->list;
	while(elem)
	{
		tmp = elem;
		elem = elem->next;
		free(tmp->room->name);
		free_list(tmp->room->list);
		free(tmp->room);
		free(tmp);
	}

	free(graph);
	return (0);
}