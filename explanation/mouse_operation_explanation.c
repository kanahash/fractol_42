/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_operation_explanation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:07:54 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 22:08:53 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// マウスのズーム操作を処理する関数
int	mouse_zoom(int key, int x, int y, t_fractol *f)
{
	double width;  // 表示領域の幅
	double height; // 表示領域の高さ
	// 表示領域の幅と高さを計算
	width = f->max_r - f->min_r;
	height = f->max_i - f->min_i;
	// ズームイン（ホイールの上向き）操作の場合
	if (key == 4)
	{
		// マウスのx座標を基準に、表示領域の最小実数部分と最大実数部分を調整
		f->min_r += width * (x / (double)WIDTH) / 5;
		f->max_r -= width * (1 - x / (double)WIDTH) / 5;
		// マウスのy座標を基準に、表示領域の最小虚数部分と最大虚数部分を調整
		f->min_i += height * (y / (double)HEIGHT) / 5;
		f->max_i -= height * (1 - y / (double)HEIGHT) / 5;
		// ズームイン時に最大イテレーション回数を増加
		f->max_iter += 2;
	}
	// ズームアウト（ホイールの下向き）操作の場合
	if (key == 5)
	{
		// マウスのx座標を基準に、表示領域の最小実数部分と最大実数部分を調整
		f->min_r -= width * (x / (double)WIDTH) / 5;
		f->max_r += width * (1 - x / (double)WIDTH) / 5;
		// マウスのy座標を基準に、表示領域の最小虚数部分と最大虚数部分を調整
		f->min_i -= height * (y / (double)HEIGHT) / 5;
		f->max_i += height * (1 - y / (double)HEIGHT) / 5;
		// ズームアウト時に最大イテレーション回数を減少（最小値30）
		if (f->max_iter > 30)
			f->max_iter -= 2;
	}
	// 処理が終わったら0を返す（イベントが正常に処理されたことを示す）
	return (0);
}
