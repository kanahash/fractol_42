/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:45:41 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 20:41:40 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_zoom(int key, int x, int y, t_fractol *f)
{
	double	width;
	double	height;

	width = f->max_r - f->min_r;
	height = f->max_i - f->min_i;
	if (key == 4)
	{
		f->min_r += width * (x / (double)WIDTH) / 5;
		f->max_r -= width * (1 - x / (double)WIDTH) / 5;
		f->min_i += height * (y / (double)HEIGHT) / 5;
		f->max_i -= height * (1 - y / (double)HEIGHT) / 5;
		f->max_iter += 2;
	}
	if (key == 5)
	{
		f->min_r -= width * (x / (double)WIDTH) / 5;
		f->max_r += width * (1 - x / (double)WIDTH) / 5;
		f->min_i -= height * (y / (double)HEIGHT) / 5;
		f->max_i += height * (1 - y / (double)HEIGHT) / 5;
		if (f->max_iter > 30)
			f->max_iter -= 2;
	}
	return (0);
}
