/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_operation_explanation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:27:36 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:27:40 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタル処理に必要なヘッダーファイルをインクルード

// マウスのスクロールイベントを処理する関数（ズームイン・ズームアウト）
int	mouse_zoom(int key, int x, int y, t_fractol *f)
{
	double	width;
	double	height;

	// フラクタルの表示範囲（実数部分と虚数部分）の幅と高さを計算
	width = f->max_r - f->min_r;  // 実数部分の幅
	height = f->max_i - f->min_i; // 虚数部分の高さ
	// スクロールアップ（ズームイン）の処理（key == 4）
	if (key == 4)
	{
		// ズームイン：マウスの位置を基準に表示範囲を縮小
		// 実数部分の範囲をマウスの位置（x座標）に応じて調整
		f->min_r += width * (x / (double)WIDTH) / 5;     // 左側の境界を動かす
		f->max_r -= width * (1 - x / (double)WIDTH) / 5; // 右側の境界を動かす
		// 虚数部分の範囲をマウスの位置（y座標）に応じて調整
		f->min_i += height * (y / (double)HEIGHT) / 5;     // 下側の境界を動かす
		f->max_i -= height * (1 - y / (double)HEIGHT) / 5; // 上側の境界を動かす
		f->max_iter += 2;
		// ズームインに合わせて反復回数を増やす（精度を上げる）
	}
	// スクロールダウン（ズームアウト）の処理（key == 5）
	if (key == 5)
	{
		// ズームアウト：マウスの位置を基準に表示範囲を拡大
		f->min_r -= width * (x / (double)WIDTH) / 5;     // 左側の境界を動かす
		f->max_r += width * (1 - x / (double)WIDTH) / 5; // 右側の境界を動かす
		// 虚数部分の範囲をマウスの位置（y座標）に応じて調整
		f->min_i -= height * (x / (double)HEIGHT) / 5;     // 下側の境界を動かす
		f->max_i += height * (1 - y / (double)HEIGHT) / 5; // 上側の境界を動かす
		// ズームアウト時、反復回数が30より大きい場合は減少
		if (f->max_iter > 30)
			f->max_iter -= 2; // 最大反復回数を減少
	}
	return (0); // 処理が終わったことを示す（0はエラーなし）
}
