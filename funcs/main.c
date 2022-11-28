/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 11:40:28 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

int	main(int ac, char *av[], char **envp)
{
	t_ppx	ppx;
	int32_t pipes[MAX_FD][2];
	// int32_t pids[MAX_FD];

	check_input(ac);
	ppx.av = av;
	ppx.envp = envp;

	count_commands(&ppx, ac);
	// printf("amount commands: %d\n", ppx.amount_cmds);
	open_files(&ppx, ac);
	open_pipes(&ppx, pipes);
	
	// // printing pipes
	// fprintf(stderr, "pipe: %d\n", pipes[0][0]);
	// fprintf(stderr, "pipe: %d\n", pipes[0][1]);
	// fprintf(stderr, "pipe: %d\n", pipes[1][0]);
	// fprintf(stderr, "pipe: %d\n", pipes[1][1]);
	// fprintf(stderr, "pipe: %d\n", pipes[2][0]);
	// fprintf(stderr, "pipe: %d\n\n", pipes[2][1]);
	// fprintf(stderr, "file 0: %d\n", ppx.file[0]);
	// fprintf(stderr, "file 1: %d\n", ppx.file[1]);

	pipex(&ppx, pipes);
	
	// if (ppx.file[0])
	// 	close(ppx.file[0]);
	// if (ppx.file[1])
	// 	close(ppx.file[1]);


	return (0);
}

