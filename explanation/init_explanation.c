/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_explanation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:23:34 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:24:03 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタルの処理に必要なヘッダーファイルをインクルード

// すべてのリソースを解放する関数
static void	release_all(t_fractol *f)
{
	// 画像が存在する場合はその画像を解放
	if (f->img.img != NULL)
		mlx_destroy_image(f->mlx, f->img.img); // mlx_destroy_imageは画像を解放する関数
	// ウィンドウが存在する場合はウィンドウを解放
	if (f->win != NULL)
		mlx_destroy_window(f->mlx, f->win); // mlx_destroy_windowはウィンドウを解放する関数
	// mlxが存在する場合はディスプレイを解放
	if (f->mlx != NULL)
	{
		mlx_destroy_display(f->mlx); // mlx_destroy_displayはディスプレイを解放する関数
		free(f->mlx);                // mlx自体のメモリを解放
	}
}

// フラクタルの設定をリセットする関数
static void	clean_data(t_fractol *f)
{
	// フラクタルの構造体内の各メンバ変数を初期化
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

// フラクタルの種類に基づいて設定を行う関数
static void	set_fractol(t_fractol *f)
{
	// フラクタルの種類が1の場合（例：マンデルブロ集合）
	if (f->kind == 1)
	{
		f->min_r = -2.2; // 最小の実数部分
		f->max_r = 1.0;  // 最大の実数部分
		f->min_i = -1.5; // 最小の虚数部分
		f->max_i = (f->max_r - f->min_r) * HEIGHT / WIDTH + f->min_i;
		// 画面の縦横比に合わせた虚数部分の最大値
		f->max_iter = 30;
		// 最大反復回数（フラクタルの精度に関わる）
		f->color = 265;
		// 使用する色の設定
	}
	// フラクタルの種類が2の場合（例：ジュリア集合）
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

// ウィンドウの初期化を行う関数
static int	init_window(t_fractol *f)
{
	// mlx_initはMLXライブラリを初期化する関数
	f->mlx = mlx_init();
	if (f->mlx == NULL) // 初期化に失敗した場合は0を返す
		return (0);
	// 新しいウィンドウを作成
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (f->win == NULL) // ウィンドウ作成に失敗した場合はリソースを解放して0を返す
	{
		release_all(f);
		return (0);
	}
	// 画像を作成（ウィンドウに表示するための画像）
	f->img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (f->img.img == NULL) // 画像作成に失敗した場合はリソースを解放して0を返す
	{
		release_all(f);
		return (0);
	}
	// 画像データのアドレスを取得
	f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bpp, &f->img.line_size,
			&f->img.endian);
	if (f->img.addr == NULL) // 画像データの取得に失敗した場合はリソースを解放して0を返す
	{
		release_all(f);
		return (0);
	}
	return (1); // 初期化が成功した場合は1を返す
}

// フラクタルデータの初期化を行う関数
int	init_data(t_fractol *f)
{
	clean_data(f); // データのクリア（初期化）
	// ウィンドウと画像の初期化
	if (!init_window(f))
		return (0); // 初期化に失敗した場合は0を返す
	set_fractol(f); // フラクタルの設定
	return (1);     // 初期化が成功した場合は1を返す
}
