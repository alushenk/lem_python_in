//
// Created by lush on 7/31/17.
//

#include "lem-in.h"

t_link	*create_link(t_room *room)
{
	t_link *result;

	result = (t_link*)malloc(sizeof(t_link));
	result->room = room;
	result->next = NULL;
	return (result);
}