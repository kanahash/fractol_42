/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboad_operation_explanation.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:01:36 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 22:06:23 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ウィンドウを閉じる処理を行う関数
int	close_window(t_fractol *f)
{
	// 画像を破棄
	mlx_destroy_image(f->mlx, f->img.img);
	// ウィンドウを破棄
	mlx_destroy_window(f->mlx, f->win);
	// 表示用の接続を破棄
	mlx_destroy_display(f->mlx);
	// mlxのメモリを解放
	free(f->mlx);
	// プログラムを終了
	exit(0);
}

// キーボードによるズーム処理
static void	keyboad_zoom(int key, t_fractol *f)
{
	double	width;
	double	height;

	// 現在の表示領域の幅と高さを計算
	width = f->max_r - f->min_r;
	height = f->max_i - f->min_i;
	// 'z'キーが押された場合、ズームイン（表示領域を縮小）
	if (key == 'z')
	{
		f->max_r -= width / 10;
		f->min_r += width / 10;
		f->max_i -= height / 10;
		f->min_i += height / 10;
		// 最大イテレーション回数を増加
		f->max_iter += 2;
	}
	// 'x'キーが押された場合、ズームアウト（表示領域を拡大）
	if (key == 'x')
	{
		f->max_r += width / 10;
		f->min_r -= width / 10;
		f->max_i += height / 10;
		f->min_i -= height / 10;
		// 最大イテレーション回数を減少（最小30）
		if (f->max_iter > 30)
			f->max_iter -= 2;
	}
}

// キーボードによる表示領域の幅の移動処理
static void	keyboad_move_width(int key, t_fractol *f)
{
	double	width;

	// 現在の表示領域の幅を計算
	width = f->max_r - f->min_r;
	// 右矢印キーが押された場合、表示領域を右に移動
	if (key == XK_Right)
	{
		f->max_r += width / 10;
		f->min_r += width / 10;
	}
	// 左矢印キーが押された場合、表示領域を左に移動
	else if (key == XK_Left)
	{
		f->max_r -= width / 10;
		f->min_r -= width / 10;
	}
}

// キーボードによる表示領域の高さの移動処理
static void	keyboad_move_height(int key, t_fractol *f)
{
	double	height;

	// 現在の表示領域の高さを計算
	height = f->max_i - f->min_i;
	// 下矢印キーが押された場合、表示領域を下に移動
	if (key == XK_Down)
	{
		f->max_i += height / 10;
		f->min_i += height / 10;
	}
	// 上矢印キーが押された場合、表示領域を上に移動
	else if (key == XK_Up)
	{
		f->max_i -= height / 10;
		f->min_i -= height / 10;
	}
}

// キーボードイベントを処理する関数
int	keyboad_event(int key, t_fractol *f)
{
	// Escapeキーが押された場合、ウィンドウを閉じる
	if (key == XK_Escape)
		close_window(f);
	// 左右矢印キーが押された場合、幅を移動
	else if (key == XK_Left || key == XK_Right)
		keyboad_move_width(key, f);
	// 上下矢印キーが押された場合、高さを移動
	else if (key == XK_Up || key == XK_Down)
		keyboad_move_height(key, f);
	// 'z'または'x'キーが押された場合、ズーム操作
	else if (key == 'z' || key == 'x')
		keyboad_zoom(key, f);
	// イベント処理が終わったら 0 を返す
	return (0);
}
