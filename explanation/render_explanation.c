/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_explanation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:09:45 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 22:11:05 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// 画像の指定された座標(x, y)に色を設定する関数
static void	img_pix_coordinate(t_img *img, int x, int y, int color)
{
	char *pixel; // 画像のピクセルデータへのポインタ
	// 画像のアドレスから、指定された座標(x, y)のピクセル位置を計算
	// (HEIGHT - y)で上下反転して、画像のメモリ配置に合わせて計算
	pixel = img->addr + ((HEIGHT - y) * img->line_size + x * (img->bpp / 8));
	// ピクセルに指定された色を設定
	*(int *)pixel = color;
}

// ジュリア集合を計算する関数
static int	julia(double x, double y, t_fractol *f)
{
	double zr;  // 実数部分
	double zi;  // 虚数部分
	double tmp; // 中間計算用変数
	int iter;   // イテレーション回数
	zr = x;     // 初期値としてxを実数部分に設定
	zi = y;     // 初期値としてyを虚数部分に設定
	iter = 0;   // 初期イテレーション回数を0に設定
	// 最大イテレーション回数まで繰り返す
	while (iter < f->max_iter)
	{
		// ジュリア集合の計算
		tmp = 2 * zr * zi - f->arg_i;
		zr = zr * zr - zi * zi + f->arg_r;
		zi = tmp;
		// 発散した場合、計算を終了
		if ((zr * zr + zi * zr) > 4)
			break ;
		iter++; // イテレーション回数を増加
	}
	return (iter); // 最終的なイテレーション回数を返す
}

// マンデルブロ集合を計算する関数
static int	mandelbrot(double x, double y, t_fractol *f)
{
	double zr;  // 実数部分
	double zi;  // 虚数部分
	double tmp; // 中間計算用変数
	int iter;   // イテレーション回数
	zr = 0;     // 初期値として実数部分を0に設定
	zi = 0;     // 初期値として虚数部分を0に設定
	iter = 0;   // 初期イテレーション回数を0に設定
	// 最大イテレーション回数まで繰り返す
	while (iter < f->max_iter)
	{
		// マンデルブロ集合の計算
		tmp = 2 * zr * zi + y;
		zr = zr * zr - zi * zi + x;
		zi = tmp;
		// 発散した場合、計算を終了
		if ((zr * zr + zi * zi) > 4)
			break ;
		iter++; // イテレーション回数を増加
	}
	return (iter); // 最終的なイテレーション回数を返す
}

// フラクタルの画像を計算して描画する関数
static void	get_fractol_image(t_fractol *f)
{
	double x;     // 画像の横方向のピクセル座標
	double y;     // 画像の縦方向のピクセル座標
	double map_r; // 実数部分のマッピング座標
	double map_i; // 虚数部分のマッピング座標
	int iter;     // イテレーション回数
	x = -1;       // 画像の横方向の初期位置を設定
	iter = 0;     // 初期イテレーション回数を0に設定
	// 画像の各ピクセルを計算して描画
	while (++x < WIDTH)
	{
		y = -1; // 縦方向のピクセル座標を初期化
		while (++y < HEIGHT)
		{
			// 座標(x, y)に対応する実数部と虚数部を計算
			map_r = f->min_r + (x * (f->max_r - f->min_r)) / WIDTH;
			map_i = f->min_i + (y * (f->max_i - f->min_i)) / HEIGHT;
			// フラクタルの種類に応じて計算
			if (f->kind == 1)
				iter = mandelbrot(map_r, map_i, f); // マンデルブロ集合
			else if (f->kind == 2)
				iter = julia(map_r, map_i, f); // ジュリア集合
			// イテレーション回数に応じて色を設定
			if (iter == f->max_iter)
				img_pix_coordinate(&f->img, x, y, 0x000000); // 発散しなかった場合は黒
			else
				img_pix_coordinate(&f->img, x, y, f->color * iter * iter);
			// 色を設定
		}
	}
}

// フラクタル画像を描画する関数
int	render(t_fractol *f)
{
	// 画面をクリア
	mlx_clear_window(f->mlx, f->win);
	// フラクタルの画像を計算
	get_fractol_image(f);
	// 計算した画像をウィンドウに表示
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
	return (1); // 描画処理が成功したことを返す
}
