/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:16:54 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/24 17:26:14 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

/*
 * function counts the amount of commands
 * later add option to count commands with including heredoc
 */
void count_commands(t_ppx *ppx, int32_t argc)
{
	ppx->amount_cmds = argc - 3;

// count commads if heredoc

}



