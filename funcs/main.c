/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/26 20:53:59 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void open_file(t_ppx *ppx, int32_t ac)
{
	// printf("av[1]: %s\n", ppx->av[1]);
	ppx->file[0] = open(ppx->av[1], O_RDONLY, 0666);
	// printf("av[ac-1]: %s\n", ppx->av[ac-1]);
	ppx->file[1] = open(ppx->av[ac-1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	
	// checking if infile is correct
    if (ppx->file[0] < 0)
        error_msg("Failed to open file 1!\n");
    if (ppx->file[1] < 0)
        error_msg("Failed to open file 2!\n");
}

int	main(int ac, char *av[], char **envp)
{
	t_ppx	ppx;
	

	check_input(ac);
	ppx.av = av;
	ppx.envp = envp;

	count_commands(&ppx, ac);
	// printf("amount commands: %d\n", ppx.amount_cmds);
	open_file(&ppx, ac);
	pipex(&ppx);
	// close(ppx.file[1]);
	// close(ppx.file[0]);
	// close(ppx.pipe[0]);
	// close(ppx.pipe[1]);

	// // creating pipe:
	// // p[0] is the reading end, so the parent cause it needs to read the passed 
	// //	command from the child to execute it
	// // p[1] is the writing end, so the cild writes to the parent the command
	// //	that the parent needs to execute
	// if (pipe(ppx.pipe) < 0)
	// 	error_msg("failed to open pipe!\n");





	
	
	return (0);
}

