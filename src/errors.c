//
// Created by lush on 7/30/17.
//

#include "lem-in.h"

void error(char *str)
{
	exit(write(2, str, ft_strlen(str)));
}