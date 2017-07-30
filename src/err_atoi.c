//
// Created by lush on 7/30/17.
//

#include "lem-in.h"

int		err_atoi(const char *str)
{
	ssize_t	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		error("Error! wrong_arguments");
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX || (result * sign < INT_MIN))
			error("Error! wrong_arguments");
		str++;
	}
	if (*str != '\0')
		error("Error! wrong_arguments");
	return (int)result * sign;
}