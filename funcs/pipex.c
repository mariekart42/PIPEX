/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:20:25 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 14:50:33 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void close_pipes(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i = 0;
	
	while (i+1 < ppx->amount_cmds)
	{
		// printf("close pipe yes: %d\n\n", i);
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (ppx->file[0])
		close(ppx->file[0]);
	if (ppx->file[1])
		close(ppx->file[1]);
}

/*
 * function counts the amount of commands
 * later add option to count commands with including heredoc
 */
void count_commands(t_ppx *ppx, int32_t ac)
{
	ppx->amount_cmds = ac - 3;
// printf("amount of processes: %d\n", ppx->amount_cmds);
// count commads if heredoc

}

void open_files(t_ppx *ppx, int32_t ac)
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

void open_pipes(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i = 0;
	
	// for 3 cmds we need 2 pipes
	while (i+1 < ppx->amount_cmds)
	{
		if (pipe(pipes[i]) < 0)
			error_msg("Failed to open pipe\n");
		i++;
	}
	// fprintf(stderr, "we have <%d> pipes\n", i);
}

void execute_cmd(t_ppx *ppx, char **cmd)
{
	char *path;

	path = get_path(ppx->envp, cmd);

	// now we can execute the cmd
	if (execve(path, cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(path);
}

// rn 2 pipes are open, everyone needs to be closed in the child processes and in the parent 
void pipex(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t cmd_num = 1;
	int32_t i = 0;
	int32_t pid = 0;
	char	**cmd;

// for 3 cmds the loop needs to run 3 times
	while (cmd_num <= ppx->amount_cmds)
	{
		
		pid = fork();
		if (pid == 0)
		{
			if (cmd_num == 1)
			{
				fprintf(stderr, "reading from file[0]\nwriting to pipe[0][1]\n\n");
				dup2(ppx->file[0], STDIN_FILENO);
				dup2(pipes[0][1], STDOUT_FILENO);
				close_pipes(ppx, pipes);
			}
			else if (cmd_num == ppx->amount_cmds)
			{
				fprintf(stderr, "reading from pipe[i-1=%d][0]\nwriting to file[1]\n\n", i-1);
				dup2(pipes[i-1][0], STDIN_FILENO);
				dup2(ppx->file[1], STDOUT_FILENO);
				close_pipes(ppx, pipes);
			}
			else
			{
				fprintf(stderr, "reading from pipe[i-1=%i][0]\nwriting to pipe[i][1]\n\n", i-1);
				dup2(pipes[i-1][0], STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
				close_pipes(ppx, pipes);
			}
			cmd = ft_split(ppx->av[cmd_num+1], ' ');
			execute_cmd(ppx, cmd);
			error_msg("Failed to execute command!");
		}
		cmd_num++;
		i++;
		// wait(NULL);
		// printf("cmd_num: %d\ni: %d\n\n", cmd_num, i);
	}
	// waitpid(pid, NULL, 0);
	close_pipes(ppx, pipes);
	// close_pipes(ppx, pipes);
}