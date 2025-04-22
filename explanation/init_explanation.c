/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_explanation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:00:18 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 22:06:02 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// メモリやリソースの解放を行う関数
static void	release_all(t_fractol *f)
{
	// 画像が存在する場合は解放
	if (f->img.img != NULL)
		mlx_destroy_image(f->mlx, f->img.img);
	// ウィンドウが存在する場合は解放
	if (f->win != NULL)
		mlx_destroy_window(f->mlx, f->win);
	// mlxが存在する場合は、表示を解放し、メモリも解放
	if (f->mlx != NULL)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
}

// fractolのデータを初期化する関数
static void	clean_data(t_fractol *f)
{
	// fractol構造体のメンバ変数を初期化
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

// fractolの種別に応じた設定を行う関数
static void	set_fractol(t_fractol *f)
{
	// fractolの種類によって初期設定を変更
	if (f->kind == 1) // JuliaやMandelbrotなど
	{
		f->min_r = -2.2; // 表示領域の最小実数部分
		f->max_r = 1.0;  // 表示領域の最大実数部分
		f->min_i = -1.5; // 表示領域の最小虚数部分
		// 表示領域の最大虚数部分は、実数部分の比率を基に計算
		f->max_i = (f->max_r - f->min_r) * HEIGHT / WIDTH + f->min_i;
		f->max_iter = 30; // 最大反復回数
		f->color = 265;   // 色の設定
	}
	else if (f->kind == 2) // 例: もう1つのフラクタル（マンデルブロ集合など）
	{
		f->min_r = -2.0; // 表示領域の最小実数部分
		f->max_r = 2.0;  // 表示領域の最大実数部分
		f->min_i = -2.0; // 表示領域の最小虚数部分
		// 表示領域の最大虚数部分を計算
		f->max_i = (f->max_r - f->min_r) * HEIGHT / WIDTH + f->min_i;
		f->max_iter = 30; // 最大反復回数
		f->color = 265;   // 色の設定
	}
}

// ウィンドウと画像の初期化を行う関数
static int	init_window(t_fractol *f)
{
	// mlxの初期化
	f->mlx = mlx_init();
	if (f->mlx == NULL) // 初期化に失敗した場合、0を返す
		return (0);
	// 新しいウィンドウを作成
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (f->win == NULL) // ウィンドウの作成に失敗した場合、リソースを解放し0を返す
	{
		release_all(f);
		return (0);
	}
	// 新しい画像を作成
	f->img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (f->img.img == NULL) // 画像の作成に失敗した場合、リソースを解放し0を返す
	{
		release_all(f);
		return (0);
	}
	// 画像のデータアドレスを取得
	f->img.addr = mlx_get_data_addr(f->img.img, &f->img.bpp, &f->img.line_size,
			&f->img.endian);
	if (f->img.addr == NULL) // アドレス取得に失敗した場合、リソースを解放し0を返す
	{
		release_all(f);
		return (0);
	}
	// すべて正常に初期化できた場合、1を返す
	return (1);
}

// fractolのデータの初期化を行う関数
int	init_data(t_fractol *f)
{
	// データの初期化
	clean_data(f);
	// ウィンドウと画像の初期化
	if (!init_window(f))
		return (0); // 初期化に失敗した場合、0を返す
	// fractolの設定を行う
	set_fractol(f);
	// 正常に初期化できた場合、1を返す
	return (1);
}
