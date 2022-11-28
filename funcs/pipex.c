/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:20:25 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 15:14:25 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void close_fds(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i = 0;
	
	while (i + 1 < ppx->amount_cmds)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (ppx->file[0])
		close(ppx->file[0]);
	if (ppx->file[1])
		close(ppx->file[1]);
}

// /*
//  * function counts the amount of commands
//  * later add option to count commands with including heredoc
//  */
// void count_commands(t_ppx *ppx, int32_t ac)
// {
// 	ppx->amount_cmds = ac - 3;
	
// // count commads if heredoc

// }

void open_files(t_ppx *ppx, int32_t ac)
{
	ppx->file[0] = open(ppx->av[1], O_RDONLY, 0666);
    if (ppx->file[0] < 0)
        error_msg("Failed to open infile!\n");
	ppx->file[1] = open(ppx->av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (ppx->file[1] < 0)
        error_msg("Failed to open outfile!\n");
}

void open_pipes(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i = 0;
	
	// for 3 cmds we need 2 pipes
	while (i + 1 < ppx->amount_cmds)
	{
		if (pipe(pipes[i]) < 0)
			error_msg("Failed to open pipe\n");
		i++;
	}
}

void execute_cmd(t_ppx *ppx, int32_t cmd_num)
{
	char *path;
	char	**cmd;

	cmd = ft_split(ppx->av[cmd_num+1], ' ');
	path = get_path(ppx->envp, cmd);

	// now we can execute the cmd
	if (execve(path, cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(path);
}

void redirect(t_ppx *ppx, int32_t pipes[MAX_FD][2], int32_t i)
{
	if (i == 0)
	{
		dup2(ppx->file[0], STDIN_FILENO);
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	else
	{
		if (i + 1 == ppx->amount_cmds)
			dup2(ppx->file[1], STDOUT_FILENO);
		else
			dup2(pipes[i][1], STDOUT_FILENO);
		dup2(pipes[i-1][0], STDIN_FILENO);
	}
}

// rn 2 pipes are open, everyone needs to be closed in the child processes and in the parent 
void pipex(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i;
	int32_t pid;
	
	i = 0;
	pid = 0;
	while (i < ppx->amount_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(ppx, pipes, i);
			close_fds(ppx, pipes);
			execute_cmd(ppx, i + 1);
			error_msg("Failed to execute command!");
		}
		i++;
	}
	waitpid(-1, NULL, 0);
	close_fds(ppx, pipes);
}
