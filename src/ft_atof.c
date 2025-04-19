/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:56:00 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/14 05:42:52 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	read_integer(char *str)
{
	double	nmb;

	nmb = 0;
	while (ft_isdigit(*str))
		nmb = nmb * 10 + *str++ - '0';
	return (nmb);
}

static double	read_decimal_point(char *str)
{
	double	nmb;
	int		power;

	nmb = 0;
	power = 1;
	while (ft_isdigit(*str))
	{
		nmb = nmb * 10 + *str++ - '0';
		power *= 10;
	}
	return (nmb / power);
}

double	ft_atof(char *str)
{
	int		sign;
	double	nmb;

	nmb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	nmb = read_integer(str);
	if (*str == '.')
		str++;
	nmb += read_decimal_point(str);
	return (sign * nmb);
}
