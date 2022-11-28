/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:14:11 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 15:16:25 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

// void check_input(int argc)
// {
// 	if (argc < 5)
// 	{
// 		write(STDERR_FILENO, \
// 		"invalid input! usage: <infile> <cmd> ... <cmd> <outfile>\n", 58);
// 		exit(EXIT_FAILURE);
// 	}
// }

void	error_msg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}