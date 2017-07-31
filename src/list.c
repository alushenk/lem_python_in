//
// Created by lush on 7/31/17.
//

#include "lem-in.h"

t_elem	*create_element(t_room *room)
{
	t_elem *result;

	result = (t_elem*)malloc(sizeof(t_elem));
	result->room = room;
	result->next = NULL;
	return (result);
}