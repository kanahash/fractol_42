/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_explanation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanahash <kanahash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:30:49 by kanahash          #+#    #+#             */
/*   Updated: 2025/04/19 12:30:52 by kanahash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h" // フラクタル処理に必要なヘッダーファイルをインクルード

// フラクタルの種類を判別する関数（引数が"マンデルブロ"または"ジュリア"の場合）
static int	get_kind_of_fractol(char *str)
{
	// "Mandelbrot" または "M" が入力された場合、マンデルブロ集合として扱う
	if (ft_strncmp(str, "Mandelbrot", 11) == 0 || ft_strncmp(str, "M", 2) == 0)
		return (1); // 1を返して、マンデルブロ集合
					// "Julia" または "J" が入力された場合、ジュリア集合として扱う
	if (ft_strncmp(str, "Julia", 6) == 0 || ft_strncmp(str, "J", 2) == 0)
		return (2); // 2を返して、ジュリア集合
	return (0);     // それ以外の入力の場合は0を返す（不正な入力）
}

// 文字列が数値かどうかをチェックする関数
static int	is_number(char *str)
{
	// 文字列が空白やタブ、改行文字で始まる場合、スキップする
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	// 数字の前に '+' または '-' があれば、それをスキップ
	if (*str == '-' || *str == '+')
		str++;
	// 最初に数字がなければ無効
	if (!ft_isdigit(*str))
		return (0);
	// 数字が続く限り、スキップして次に進む
	while (ft_isdigit(*str))
		str++;
	// 小数点があれば、さらに数値をチェック
	if (*str == '.')
	{
		str++;                 // 小数点をスキップ
		if (!ft_isdigit(*str)) // 小数点の後に数字がなければ無効
			return (0);
		while (ft_isdigit(*str)) // 小数点の後に数字が続く限り進む
			str++;
	}
	// 文字列の終わりまで到達すれば有効な数値
	if (!*str)
		return (1);
	return (0); // それ以外の不正な文字があれば無効
}

// ジュリア集合のパラメータが正しいかをチェックする関数
static int	is_julia_prm(int ac, char **av, t_fractol *f)
{
	// 引数が2つの場合、ジュリア集合には必要なパラメータが不足しているので無効
	if (ac == 2)
		return (0);
	// 2番目と3番目の引数が数値かどうかをチェック
	if (!is_number(av[2]) || !is_number(av[3]))
		return (0);
	// 引数を浮動小数点数に変換
	f->arg_r = ft_atof(av[2]); // 2番目の引数を実数部分としてセット
	f->arg_i = ft_atof(av[3]); // 3番目の引数を虚数部分としてセット
	// 引数が指定された範囲内に収まっているかチェック
	if (f->arg_r < -2.0 || f->arg_r > 2.0)
		return (0); // 実数部分が-2.0から2.0の範囲外なら無効
	if (f->arg_i <= -2.0 || f->arg_i >= 2.0)
		return (0); // 虚数部分が-2.0より小さいか2.0より大きければ無効
	return (1);     // パラメータが有効な場合は1を返す
}

// 引数の検証を行うメイン関数
int	validate(int ac, char **av, t_fractol *f)
{
	// 引数が不正（1つ未満、4つ以上、または3つの場合）ならエラーメッセージを表示
	if (ac < 2 || ac > 4 || ac == 3)
		return (msg_error()); // 無効な引数数の場合、エラーメッセージを表示
	// フラクタルの種類を取得
	f->kind = get_kind_of_fractol(av[1]);
	if (f->kind == 0)         // フラクタルの種類が無効な場合
		return (msg_error()); // エラーメッセージを表示
	// マンデルブロ集合の場合、引数は2つだけ
	if (f->kind == 1 && ac != 2)
		return (msg_error()); // 引数数が適切でなければエラーメッセージを表示
	// ジュリア集合の場合、パラメータが適切かをチェック
	if (f->kind == 2 && !is_julia_prm(ac, av, f))
		return (msg_julia_prm()); // ジュリア集合のパラメータが不正であればメッセージを表示
	return (1);                   // すべての検証を通過した場合、1を返す
}
