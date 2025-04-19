/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg_explanation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:29:22 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:29:25 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタル処理に必要なヘッダーファイルをインクルード

// エラーメッセージと使用方法を表示する関数
int	msg_error(void)
{
	// エラーメッセージを標準エラー出力（2番）に表示
	ft_putendl_fd("=================== How To Use ====================", 2);
	// ヘッダー
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("Usage example : ./fractol <type> <prm1*> <prm2*>", 2);
	// 実行例
	ft_putendl_fd(" * : Julia needs two parameters", 2);
	// Juliaの場合は2つのパラメータが必要
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("[type]", 2);
	// フラクタルのタイプの案内
	ft_putendl_fd("  Mandelbrot  /  M", 2);
	// マンデルブロ集合
	ft_putendl_fd("  Julia       /  J", 2);
	// ジュリア集合
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("==================================================", 2);
	// フッター
	return (0);
	// メッセージを表示した後に0を返す
}

// Julia集合のパラメータの使い方を表示する関数
int	msg_julia_prm(void)
{
	// Juliaのパラメータに関するガイドメッセージを表示
	ft_putendl_fd("=================== How To Use ====================", 2);
	// ヘッダー
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("Usage example : ./fractol Julia <prm1> <prm2>", 2);
	// 実行例
	ft_putendl_fd(" ! parameter must be between -2.0 and 2.0 !", 2);
	// パラメータ範囲の指定
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("[recommended parameter]", 2);
	// 推奨されるパラメータ例
	ft_putendl_fd("  -0.70176 -0.3842", 2);
	// 推奨例1
	ft_putendl_fd("  -0.8 0.156", 2);
	// 推奨例2
	ft_putendl_fd("  0.3 0.01", 2);
	// 推奨例3
	ft_putendl_fd("  0.45 0.35", 2);
	// 推奨例4
	ft_putendl_fd("", 2);
	// 空行
	ft_putendl_fd("==================================================", 2);
	// フッター
	return (0);
	// メッセージを表示した後に0を返す
}

// フラクタル操作に関するガイドメッセージを表示する関数
int	msg_operation(void)
{
	// ユーザーに操作方法を案内するメッセージ
	ft_putendl_fd("=================== How To Use ====================", 1);
	// ヘッダー
	ft_putendl_fd("", 1);
	// 空行
	ft_putendl_fd("zoom : scroll mouse wheel  or  'z' / 'x'", 1);
	// ズーム操作の案内（マウスホイールまたはz/xキー）
	ft_putendl_fd("move : push arrow keys ", 1);
	// 移動操作の案内（矢印キー）
	ft_putendl_fd("", 1);
	// 空行
	ft_putendl_fd("==================================================", 1);
	// フッター
	return (0);
	// メッセージを表示した後に0を返す
}
