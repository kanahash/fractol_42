/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:19:23 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 11:24:37 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol	f;

	if (!validate(ac, av, &f))
		return (-1);
	if (!init_data(&f))
		return (0);
	msg_operation();
	mlx_loop_hook(f.mlx, &render, &f);
	mlx_hook(f.win, 2, 1L << 0, &keyboad_event, &f);
	mlx_hook(f.win, 4, 1L << 2, &mouse_zoom, &f);
	mlx_hook(f.win, 17, 0L, &close_window, &f);
	mlx_loop(f.mlx);
	return (0);
}
