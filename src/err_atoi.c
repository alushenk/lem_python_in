/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alushenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:22:50 by alushenk          #+#    #+#             */
/*   Updated: 2017/08/04 10:22:51 by alushenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
		error("Error! wrong_arguments\n");
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX || (result * sign < INT_MIN))
			error("Error! wrong_arguments\n");
		str++;
	}
	if (*str != '\0')
		error("Error! wrong_arguments\n");
	return (int)result * sign;
}
