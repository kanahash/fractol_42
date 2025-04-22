/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_explanation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 22:12:04 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/22 22:12:30 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// フラクタルの種類を判定する関数
static int	get_kind_of_fractol(char *str)
{
	// "Mandelbrot" または "M" と一致すれば、マンデルブロ集合を選択
	if (ft_strncmp(str, "Mandelbrot", 11) == 0 || ft_strncmp(str, "M", 2) == 0)
		return (1);
	// "Julia" または "J" と一致すれば、ジュリア集合を選択
	if (ft_strncmp(str, "Julia", 6) == 0 || ft_strncmp(str, "J", 2) == 0)
		return (2);
	// 一致しない場合は、0を返す（無効なフラクタル種類）
	return (0);
}

// 文字列が数値かどうかを確認する関数
static int	is_number(char *str)
{
	// 文字列の先頭にある空白文字（スペース、タブ、改行など）をスキップ
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	// 数字の前に符号がある場合、符号をスキップ
	if (*str == '-' || *str == '+')
		str++;
	// 最初の数字がなければ無効
	if (!ft_isdigit(*str))
		return (0);
	// 数字部分を読み進める
	while (ft_isdigit(*str))
		str++;
	// 小数点があれば小数部も処理する
	if (*str == '.')
	{
		str++;
		// 小数部がなければ無効
		if (!ft_isdigit(*str))
			return (0);
		// 小数部の数字を読み進める
		while (ft_isdigit(*str))
			str++;
	}
	// 文字列の終わりまで進んだ場合、数値として有効
	if (!*str)
		return (1);
	// それ以外は無効
	return (0);
}

// ジュリア集合のパラメータ（引数）を検証する関数
static int	is_julia_prm(int ac, char **av, t_fractol *f)
{
	// ジュリア集合の場合、引数が2つでなければ無効
	if (ac == 2)
		return (0);
	// 引数2と3が数値でなければ無効
	if (!is_number(av[2]) || !is_number(av[3]))
		return (0);
	// 引数2（実数部分）が-2.0～2.0の範囲外であれば無効
	f->arg_r = ft_atof(av[2]);
	f->arg_i = ft_atof(av[3]);
	if (f->arg_r < -2.0 || f->arg_r > 2.0)
		return (0);
	// 引数3（虚数部分）が-2.0～2.0の範囲外であれば無効
	if (f->arg_i <= -2.0 || f->arg_i >= 2.0)
		return (0);
	// パラメータが有効であれば1を返す
	return (1);
}

// コマンドライン引数を検証する関数
int	validate(int ac, char **av, t_fractol *f)
{
	// 引数が不正であればエラーメッセージを表示
	if (ac < 2 || ac > 4 || ac == 3)
		return (msg_error());
	// フラクタルの種類を取得
	f->kind = get_kind_of_fractol(av[1]);
	// 無効なフラクタル種類が指定された場合、エラーメッセージを表示
	if (f->kind == 0)
		return (msg_error());
	// マンデルブロ集合の場合、引数が2つでなければエラー
	if (f->kind == 1 && ac != 2)
		return (msg_error());
	// ジュリア集合の場合、引数のチェックを行う
	if (f->kind == 2 && !is_julia_prm(ac, av, f))
		return (msg_julia_prm());
	// 引数が有効であれば1を返す
	return (1);
}
