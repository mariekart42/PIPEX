/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:16:54 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/24 20:57:06 by mmensing         ###   ########.fr       */
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

void handle_first_cmd(t_ppx *ppx)
{
	char    *infile_path;
    char    **cmd_1 = NULL;

    
    // open outfile we need to:
	// O_RDONLY	-> read only
	// 0644		-> files owner can read and write, the others only read
	ppx->file[0] = open(ppx->argv[1], O_RDONLY | 0644);
    
    // checking if infile is correct
    if (ppx->file[0] < 0)
        error_msg("Failed to open file in first process!\n");

	// p[1] here is our write end, so we dont need the read end
	close(pipe[0]);
	
	// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
	// for this we redirect stdin to infile
	dup2(file[0], STDIN_FILENO);
	
	// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
	// the output to writing end of our pipe (p[1])
	dup2(pipe[1], STDOUT_FILENO);

    // 2d array of all commands + NULL-terminated
    cmd_1 = ft_split(argv[2], ' ');
	
    // infile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd_1 gets attached at the end 
    infile_path = get_path(envp, cmd_1);

	// now we can execute the cmd1
	if (execve(infile_path, cmd_1, envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(infile_path);
}

void pipe_cmd(t_ppx *ppx, int32_t cmd_num)
{
	// if its the first cmd
	if (cmd_num == 1)
	{
		handle_first_cmd(ppx);
	}	// if its not the last cmd
	else if (cmd_num != ppx->amount_cmds)
	{

	}	// if its the last cmd
	else
	{

	}
	

}

void pipex(t_ppx *ppx)
{
	int32_t cmd_num = 1;
	int32_t child = 0;
	
	while (amount_cmds > cmd_num)
	{
		child = fork();
		if (child < 0)
			return (perror("Fork: "));
		// means its parent
		if (child != 0)
			break ;
		pipe_cmd(ppx, cmd_num);
		cmd_num++;
	}
}

