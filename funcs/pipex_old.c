/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:16:54 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/27 13:17:54 by mmensing         ###   ########.fr       */
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


void execute_cmd(t_ppx *ppx, int32_t cmd_num, char **cmd)
{
	char	*cmd_path;

	// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
	// for this we redirect stdin to infile 
	// -> only for the very first cmd, otherwise we read from prev pipe
	if (cmd_num == 1)
	{
		close(ppx->pipe[0]);
		dup2(ppx->file[0], STDIN_FILENO);
	}
	else if (cmd_num == ppx->amount_cmds)
	{
		close(ppx->pipe[1]);
		dup2(ppx->pipe[0], STDIN_FILENO);
	}
	else
		dup2(ppx->save_prev_pipe_end, STDIN_FILENO);
		
	
	// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
	// the output to writing end of our pipe (p[1])
	// -> except for the last cmd, there we redirect the writing end to the outfile
	if (ppx->amount_cmds == cmd_num)
		dup2(ppx->file[1], STDOUT_FILENO);
	else
	{
		dup2(ppx->pipe[1], STDOUT_FILENO);
		// ppx->prev_ = ppx->pipe[0];
	}
		
	// outfile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd gets attached at the end 
    cmd_path = get_path(ppx->envp, cmd);

	if (execve(cmd_path, cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in second child!\n");
}




void pipex(t_ppx *ppx)
{
	int32_t cmd_num = 1;
	int32_t pid = 0;
	char	**cmd;
	
	op
	while (cmd_num <= ppx->amount_cmds)
	{
		printf("cmd_num: %d\n\n", cmd_num);
		if (cmd_num != ppx->amount_cmds)
		{
			if (cmd_num != 1)
				ppx->save_prev_pipe_end = ppx->pipe[0];
				// ppx->save_prev_pipe_end = ppx->pipe[0]; // using dup function here?
			if (pipe(ppx->pipe) < 0)
				error_msg("failed to open pipe!\n");
		}
		pid = fork();
		if (pid == 0)
		{
			// 2d array of all commands + NULL-terminated
			cmd = ft_split(ppx->av[cmd_num+1], ' ');
			printf("\nav[cmd+1]: %s\n\n", ppx->av[cmd_num+1]);

			execute_cmd(ppx, cmd_num, cmd);
			printf("after execute cmd\n");

			fprintf(stderr, "after execute cmd\n");
		}
		cmd_num++;
		waitpid(pid, NULL, 0);
	}
	close(ppx->file[0]);
	close(ppx->file[1]);
}