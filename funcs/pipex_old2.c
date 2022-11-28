/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_old2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 13:18:13 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 10:22:19 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

/*
 * function counts the amount of commands
 * later add option to count commands with including heredoc
 */
void count_commands(t_ppx *ppx, int32_t ac)
{
	ppx->amount_cmds = ac - 3;
printf("am of processes: %d\n", ppx->amount_cmds);
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
	while (i < ppx->amount_cmds)
	{
		if (pipe(pipes[i]) < 0)
			error_msg("Failed to open pipe\n");
		i++;
	}
}

void execute_cmd(t_ppx *ppx, char **cmd)
{
	char *path;

	path = get_path(ppx->envp, cmd);

// fprintf(stderr, "cmd: %s\n", cmd[0]);	
// fprintf(stderr, "cmd: %s\n", cmd[1]);	
// fprintf(stderr, "cmd: %s\n\n", cmd[2]);	

// fprintf(stderr, "path: %s\n\n", path);

	// now we can execute the cmd
	if (execve(path, cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(path);
}

void close_pipes(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i = 0;
	
	while (i < ppx->amount_cmds)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void pipex(t_ppx *ppx, int32_t pipes[MAX_FD][2], int32_t pids[MAX_FD])
{
	int32_t cmd_num = 1;
	int32_t	i = 0;
	char	**cmd;
	while (cmd_num <= ppx->amount_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			fprintf(stderr, "pipex while\n");
			if (cmd_num == 1)
			{
				close(pipes[0][0]);
				close(pipes[1][1]);
				close(pipes[1][0]);
				dup2(ppx->file[0], STDIN_FILENO);
				dup2(pipes[0][1], STDOUT_FILENO);
			}
			else if (cmd_num == ppx->amount_cmds)
			{
				// execute last to outfile
				dup2(pipes[i-1][1], STDIN_FILENO);
				dup2(ppx->file[1], STDOUT_FILENO);
			}
			else
			{
				dup2(pipes[i-1][0], STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
			}
			cmd = ft_split(ppx->av[cmd_num+1], ' ');
			execute_cmd(ppx, cmd);
		}
		cmd_num++;
		i++;
		fprintf(stderr, "cmd_num: %d\ni: %d\n\n", cmd_num, i);
	}
	waitpid(-1, NULL, 0);
	close_pipes(ppx, pipes);
}