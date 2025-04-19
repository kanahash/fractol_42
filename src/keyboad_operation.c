/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboad_operation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:45:24 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/17 19:45:29 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_fractol *f)
{
	mlx_destroy_image(f->mlx, f->img.img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
	exit(0);
}

static void	keyboad_zoom(int key, t_fractol *f)
{
	double	width;
	double	height;

	width = f->max_r - f->min_r;
	height = f->max_i - f->min_i;
	if (key == 'z')
	{
		f->max_r -= width / 10;
		f->min_r += width / 10;
		f->max_i -= height / 10;
		f->min_i += height / 10;
		f->max_iter += 2;
	}
	if (key == 'x')
	{
		f->max_r += width / 10;
		f->min_r -= width / 10;
		f->max_i += height / 10;
		f->min_i -= height / 10;
		if (f->max_iter > 30)
			f->max_iter -= 2;
	}
}

static void	keyboad_move_width(int key, t_fractol *f)
{
	double	width;

	width = f->max_r - f->min_r;
	if (key == XK_Right)
	{
		f->max_r += width / 10;
		f->min_r += width / 10;
	}
	else if (key == XK_Left)
	{
		f->max_r -= width / 10;
		f->min_r -= width / 10;
	}
}

static void	keyboad_move_height(int key, t_fractol *f)
{
	double	height;

	height = f->max_i - f->min_i;
	if (key == XK_Down)
	{
		f->max_i += height / 10;
		f->min_i += height / 10;
	}
	else if (key == XK_Up)
	{
		f->max_i -= height / 10;
		f->min_i -= height / 10;
	}
}

int	keyboad_event(int key, t_fractol *f)
{
	if (key == XK_Escape)
		close_window(f);
	else if (key == XK_Left || key == XK_Right)
		keyboad_move_width(key, f);
	else if (key == XK_Up || key == XK_Down)
		keyboad_move_height(key, f);
	else if (key == 'z' || key == 'x')
		keyboad_zoom(key, f);
	return (0);
}
