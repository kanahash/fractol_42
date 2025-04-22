/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_explanation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:59:02 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 21:59:09 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractol f; // fractol構造体のインスタンスを作成
	// 引数の検証とデータの初期化を行う。失敗した場合は -1 を返して終了
	if (!validate(ac, av, &f))
		return (-1);
	// fractol構造体のデータを初期化する。失敗した場合は 0 を返して終了
	if (!init_data(&f))
		return (0);
	// 操作に関するメッセージを表示する関数
	msg_operation();
	// フレームごとの描画処理を行うフック。mlx_loop_hookで定期的に呼ばれる
	mlx_loop_hook(f.mlx, &render, &f);
	// キーボードイベントを処理するためのフック。キー入力を受け取って処理
	mlx_hook(f.win, 2, 1L << 0, &keyboad_event, &f);
	// マウスのズームイベントを処理するフック。マウスのスクロールやクリックでズーム
	mlx_hook(f.win, 4, 1L << 2, &mouse_zoom, &f);
	// ウィンドウを閉じるイベントを処理するフック。ウィンドウを閉じたときに呼ばれる
	mlx_hook(f.win, 17, 0L, &close_window, &f);
	// mlx_loop を開始。イベントループが実行され、ウィンドウや描画の更新が行われる
	mlx_loop(f.mlx);
	// 終了時に0を返す
	return (0);
}
