/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_explanation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:29:30 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:29:43 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタル処理に必要なヘッダーファイルをインクルード

// ピクセルの座標に色を設定する関数
static void	img_pix_coordinate(t_img *img, int x, int y, int color)
{
	char	*pixel;

	// ピクセルのアドレスを計算（画像のアドレスにx,y座標から計算したオフセットを加える）
	pixel = img->addr + (y * img->line_size + x * (img->bpp / 8));
	// 計算したアドレスに色を設定
	*(int *)pixel = color; // 色はint型（4バイト）で設定
}

// ジュリア集合を計算する関数
static int	julia(double x, double y, t_fractol *f)
{
	double	zr;
	double	zi;
	double	tmp;
	int		iter;

	zr = x;   // ジュリア集合の実数部分
	zi = y;   // ジュリア集合の虚数部分
	iter = 0; // 反復回数のカウンタ
	// 反復処理を開始（最大反復回数に達するか、発散するまで計算）
	while (iter < f->max_iter)
	{
		tmp = 2 * zr * zi - f->arg_i;      // 計算式の一部
		zr = zr * zr - zi * zi + f->arg_r; // 実数部分の更新
		zi = tmp;                          // 虚数部分の更新
		// 発散判定（発散した場合は反復を終了）
		if ((zr * zr + zi * zi) > 4)
			break ;
		iter++; // 反復回数を増やす
	}
	return (iter); // 反復回数を返す
}

// マンデルブロ集合を計算する関数
static int	mandelbrot(double x, double y, t_fractol *f)
{
	double	zr;
	double	zi;
	double	tmp;
	int		iter;

	zr = 0;   // マンデルブロ集合の初期実数部分
	zi = 0;   // マンデルブロ集合の初期虚数部分
	iter = 0; // 反復回数のカウンタ
	// 反復処理を開始（最大反復回数に達するか、発散するまで計算）
	while (iter < f->max_iter)
	{
		tmp = 2 * zr * zi + y;      // 計算式の一部
		zr = zr * zr - zi * zi + x; // 実数部分の更新
		zi = tmp;                   // 虚数部分の更新
		// 発散判定（発散した場合は反復を終了）
		if ((zr * zr + zi * zi) > 4)
			break ;
		iter++; // 反復回数を増やす
	}
	return (iter); // 反復回数を返す
}

// フラクタル画像を生成する関数
static void	get_fractol_image(t_fractol *f)
{
	double	x;
	double	y;
	double	map_r;
	double	map_i;
	int		iter;

	x = -1;   // x座標を初期化
	iter = 0; // 反復回数の初期化
	// 画像の横方向（x軸）をループ
	while (++x < WIDTH)
	{
		y = -1; // y座標を初期化
		// 画像の縦方向（y軸）をループ
		while (++y < HEIGHT)
		{
			// 各ピクセルの座標をフラクタルの実数部と虚数部にマッピング
			map_r = f->min_r + (x * (f->max_r - f->min_r)) / WIDTH;
			map_i = f->min_i + (y * (f->max_i - f->min_i)) / HEIGHT;
			// フラクタルの種類に応じて計算を行う
			if (f->kind == 1)
				iter = mandelbrot(map_r, map_i, f); // マンデルブロ集合
			else if (f->kind == 2)
				iter = julia(map_r, map_i, f); // ジュリア集合
			// 計算結果に基づいて色を設定
			if (iter == f->max_iter)
				img_pix_coordinate(&f->img, x, y, 0x000000); // 発散しなかった場合（黒色）
			else
				img_pix_coordinate(&f->img, x, y, f->color * iter * iter);
			// 発散した場合、色を設定
		}
	}
}

// 画面を描画する関数
int	render(t_fractol *f)
{
	// ウィンドウをクリア
	mlx_clear_window(f->mlx, f->win);
	// フラクタル画像を生成
	get_fractol_image(f);
	// 生成した画像をウィンドウに表示
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
	return (1); // 描画が完了したことを示す
}
