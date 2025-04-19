/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboad_operation_explanation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:26:02 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:26:06 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタルの処理に必要なヘッダーファイルをインクルード

// ウィンドウを閉じる関数
int	close_window(t_fractol *f)
{
	// 画像、ウィンドウ、ディスプレイのメモリを解放
	mlx_destroy_image(f->mlx, f->img.img); // 画像を解放
	mlx_destroy_window(f->mlx, f->win);    // ウィンドウを解放
	mlx_destroy_display(f->mlx);           // ディスプレイを解放
	free(f->mlx);                          // mlxのメモリを解放
	exit(0);                               // プログラムを終了
}

// キーボードによるズーム処理（'z'でズームイン、'x'でズームアウト）
static void	keyboad_zoom(int key, t_fractol *f)
{
	double	width;
	double	height;

	// 表示範囲の幅と高さを計算
	width = f->max_r - f->min_r;
	height = f->max_i - f->min_i;
	// 'z'キーでズームイン：表示範囲を狭め、反復回数を増加
	if (key == 'z')
	{
		f->max_r -= width / 10;  // 右側の境界を縮小
		f->min_r += width / 10;  // 左側の境界を拡大
		f->max_i -= height / 10; // 上側の境界を縮小
		f->min_i += height / 10; // 下側の境界を拡大
		f->max_iter += 2;        // 最大反復回数を増加
	}
	// 'x'キーでズームアウト：表示範囲を広げ、反復回数を減少
	if (key == 'x')
	{
		f->max_r += width / 10;  // 右側の境界を拡大
		f->min_r -= width / 10;  // 左側の境界を縮小
		f->max_i += height / 10; // 上側の境界を拡大
		f->min_i -= height / 10; // 下側の境界を縮小
		if (f->max_iter > 30)    // 最大反復回数が30より大きい場合のみ減少
			f->max_iter -= 2;    // 最大反復回数を減少
	}
}

// キーボードによる横方向の移動処理（矢印キー左・右）
static void	keyboad_move_width(int key, t_fractol *f)
{
	double	width;

	// 表示範囲の幅を計算
	width = f->max_r - f->min_r;
	// 右矢印キーで横方向を右に移動
	if (key == XK_Right)
	{
		f->max_r += width / 10; // 右側の境界を右に移動
		f->min_r += width / 10; // 左側の境界を右に移動
	}
	// 左矢印キーで横方向を左に移動
	else if (key == XK_Left)
	{
		f->max_r -= width / 10; // 右側の境界を左に移動
		f->min_r -= width / 10; // 左側の境界を左に移動
	}
}

// キーボードによる縦方向の移動処理（矢印キー上・下）
static void	keyboad_move_height(int key, t_fractol *f)
{
	double	height;

	// 表示範囲の高さを計算
	height = f->max_i - f->min_i;
	// 下矢印キーで縦方向を下に移動
	if (key == XK_Down)
	{
		f->max_i += height / 10; // 上側の境界を下に移動
		f->min_i += height / 10; // 下側の境界を下に移動
	}
	// 上矢印キーで縦方向を上に移動
	else if (key == XK_Up)
	{
		f->max_i -= height / 10; // 上側の境界を上に移動
		f->min_i -= height / 10; // 下側の境界を上に移動
	}
}

// キーボードイベントを処理する関数
int	keyboad_event(int key, t_fractol *f)
{
	// 'Esc'キーが押された場合、ウィンドウを閉じる
	if (key == XK_Escape)
		close_window(f);
	// 矢印キー（左右）で横方向の移動を処理
	else if (key == XK_Left || key == XK_Right)
		keyboad_move_width(key, f);
	// 矢印キー（上下）で縦方向の移動を処理
	else if (key == XK_Up || key == XK_Down)
		keyboad_move_height(key, f);
	// 'z'キーでズームイン、'x'キーでズームアウト
	else if (key == 'z' || key == 'x')
		keyboad_zoom(key, f);
	return (0); // イベント処理が終わったことを示す
}
