/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 15:20:50 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void check_and_init_data(t_ppx *ppx, int32_t ac, char **av, char **envp)
{
	if (ac < 5)
	{
		write(STDERR_FILENO, \
		"invalid input! usage: <infile> <cmd> ... <cmd> <outfile>\n", 58);
		exit(EXIT_FAILURE);
	}
	ppx->av = av;
	ppx->envp = envp;
	
	// set ammount cmds
	// without heredoc:
	ppx->amount_cmds = ppx->amount_cmds = ac - 3;
}

int	main(int ac, char *av[], char **envp)
{
	t_ppx	ppx;
	int32_t pipes[MAX_FD][2];

	check_and_init_data(&ppx, ac, av, envp);
	open_files(&ppx, ac);
	open_pipes(&ppx, pipes);
	pipex(&ppx, pipes);
	return (0);
}
