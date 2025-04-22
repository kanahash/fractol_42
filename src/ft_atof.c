/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:56:00 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 20:09:06 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atof(const char *str)
{
	int		sign;
	double	nmb;
	int		power;

	nmb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
		nmb = nmb * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	power = 1;
	while (ft_isdigit(*str))
	{
		nmb = nmb * 10 + (*str++ - '0');
		power *= 10;
	}
	return (sign * nmb / power);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	double ans;

// 	// char *str = "     -+3549.26594    "; // 0.000000
// 	// char *str = "     -3549.26594    "; // -3549.265940
// 	// char    *str = "     -3549.26h594    "; // -3549.260000
// 	// char *str = "    -"; // -3549.260000
// 	ans = ft_atof(str);
// 	printf("%f\n", ans);
// 	return (0);
// }