/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:07:42 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/17 21:02:32 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_kind_of_fractol(char *str)
{
	if (ft_strncmp(str, "Mandelbrot", 11) == 0 || ft_strncmp(str, "M", 2) == 0)
		return (1);
	if (ft_strncmp(str, "Julia", 6) == 0 || ft_strncmp(str, "J", 2) == 0)
		return (2);
	return (0);
}
static int	is_number(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		if (!ft_isdigit(*str))
			return (0);
		while (ft_isdigit(*str))
			str++;
	}
	if (!*str)
		return (1);
	return (0);
}

static int	is_julia_prm(int ac, char **av, t_fractol *f)
{
	if (ac == 2)
		return (0);
	if (!is_number(av[2]) || !is_number(av[3]))
		return (0);
	f->arg_r = ft_atof(av[2]);
	f->arg_i = ft_atof(av[3]);
	if (f->arg_r < -2.0 || f->arg_r > 2.0)
		return (0);
	if (f->arg_i <= -2.0 || f->arg_i >= 2.0)
		return (0);
	return (1);
}

int	validate(int ac, char **av, t_fractol *f)
{
	if (ac < 2 || ac > 4 || ac == 3)
		return (msg_error());
	f->kind = get_kind_of_fractol(av[1]);
	if (f->kind == 0)
		return (msg_error());
	if (f->kind == 1 && ac != 2)
		return (msg_error());
	if (f->kind == 2 && !is_julia_prm(ac, av, f))
		return (msg_julia_prm());
	return (1);
}
