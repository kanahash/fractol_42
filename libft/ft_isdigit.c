/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 05:14:47 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 10:48:23 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
	{
		return (LINUX_TRUE);
	}
	return (LINUX_FALSE);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int	c;

// 	c = '0';
// 	printf("<ft_isdigit> : %d\n", ft_isdigit(c));
// 	printf("<isdigit> : %d\n", isdigit(c));
// 	return (0);
// }