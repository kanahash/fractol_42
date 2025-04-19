/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:10:45 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 10:54:22 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	release_all(t_fractol *f)
{
	if (f->img.img != NULL)
		mlx_destroy_image(f->mlx, f->img.img);
	if (f->win != NULL)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx != NULL)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
}

static void	clean_data(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->max_r = 0;
	f->max_i = 0;
	f->min_r = 0;
	f->max_iter = 0;
	f->color = 0;
	f->img.img = NULL;
	f->img.addr = NULL;
	f->img.bpp = 0;
	f->img.line_size = 0;
	f->img.endian = 0;
}

static void	set_fractol(t_fractol *f)
{
	if (f->kind == 1)
	{
		f->min_r = -2.2;
		f->max_r = 1.0;
		f->min_i = -1.5;
		f->max_i = (f->max_r - f->min_r) * HEIGHT / WIDTH + f->min_i;
		f->max_iter = 30;
		f->color = 265;
	}
	else if (f->kind == 2)
	{
		f->min_r = -2.0;
		f->max_r = 2.0;
		f->min_i = -2.0;
		f->max_i = (f->max_r - f->min_r) * HEIGHT / WIDTH + f->min_i;
		f->max_iter = 30;
		f->color = 265;
	}
}

static int	init_window(t_fractol *f)
{
	f->mlx = mlx_init();
	if (f->mlx == NULL)
		return (0);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (f->win == NULL)
	{
		release_all(f);
		return (0);
	}
	f->img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (f->img.img == NULL)
	{
		release_all(f);
		return (0);
	}
	f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bpp, &f->img.line_size,
			&f->img.endian);
	if (f->img.addr == NULL)
	{
		release_all(f);
		return (0);
	}
	return (1);
}

int	init_data(t_fractol *f)
{
	clean_data(f);
	if (!init_window(f))
		return (0);
	set_fractol(f);
	return (1);
}
