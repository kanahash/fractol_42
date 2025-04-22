/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 04:05:24 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 20:11:23 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define LINUX_TRUE 2048
# define LINUX_FALSE 0

# define WIDTH 1000
# define HEIGHT 1000

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img;
	void	*addr;
	int		bpp;
	int		line_size;
	int		endian;
}			t_img;

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	int		kind;
	double	arg_r;
	double	arg_i;
	double	max_r;
	double	max_i;
	double	min_r;
	double	min_i;
	double	max_iter;
	int		color;
	t_img	img;
}			t_fractol;

// libft
int			ft_isdigit(int c);
void		ft_putendl_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// src
// ft_atof.c
double		ft_atof(const char *str);

// init.c
int			init_data(t_fractol *f);

// keyboad_operation.c
int			close_window(t_fractol *f);
int			keyboad_event(int key, t_fractol *f);

// mouse_operation.c
int			mouse_zoom(int key, int x, int y, t_fractol *f);

// print_msg.c
int			msg_error(void);
int			msg_julia_prm(void);
int			msg_operation(void);

// render.c
int			render(t_fractol *f);

// validate.c
int			validate(int ac, char **av, t_fractol *f);

#endif
