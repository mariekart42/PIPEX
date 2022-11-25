/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:16:54 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/25 15:06:46 by mmensing         ###   ########.fr       */
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

void handle_cmd(t_ppx *ppx)
{
	char    *path;
    // char    **cmd_2 = NULL;
	
	// file[1] is a temporary file that needs to be deleted in the end
	ppx->file[1] = open("tmp", O_RDONLY | 0644);
    
    // checking if infile is correct
    if (ppx->file[1] < 0)
        error_msg("Failed to open file in second child!\n");
		
	// p[0] here is our read end, so we dont need the write end
	close(ppx->pipe[1]);
	
	// instead of outputting the result from our exeve in our terminal, we want it in file2
	dup2(ppx->file[1], STDOUT_FILENO);
	
	// and because the execve function needs something to read from we have to tell it, that the
	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
	// so we change stdin to the end of the pipe (p[0])
	dup2(ppx->pipe[0], STDIN_FILENO);

    // path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd gets attached at the end 
    path = get_path(ppx->envp, ppx->cmd);
    // printf("outfile peth: %s\n", outfile_path);
	
	

	// now we can execute the cmd1
	if(execve(path, ppx->cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in second child!\n");
	free(path);
}

void handle_first_cmd(t_ppx *ppx)
{
	char    *infile_path;

    // open outfile we need to:
	// O_RDONLY	-> read only
	// 0644		-> files owner can read and write, the others only read
	ppx->file[0] = open(ppx->argv[1], O_RDONLY | 0644);
    
    // checking if infile is correct
    if (ppx->file[0] < 0)
        error_msg("Failed to open file in first process!\n");

	// p[1] here is our write end, so we dont need the read end
	close(ppx->pipe[0]);
	
	// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
	// for this we redirect stdin to infile
	dup2(ppx->file[0], STDIN_FILENO);
	
	// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
	// the output to writing end of our pipe (p[1])
	dup2(ppx->pipe[1], STDOUT_FILENO);
	
    // infile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd gets attached at the end 
    infile_path = get_path(ppx->envp, ppx->cmd);

	// now we can execute the cmd
	if (execve(infile_path, ppx->cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(infile_path);
}

void handle_last_cmd(t_ppx *ppx)
{
	char    *outfile_path;
    // char    **cmd_2 = NULL;
	
    // open outfile we need to:
	// O_RDWR	-> read and write
	// O_CREAT	-> create if it doesn't exist
	// O_TRUNC	-> len always truncated to 0
	// 0777		-> full access lol
	ppx->file[1] = open("OUTFILE_", O_RDWR | O_TRUNC | O_CREAT);//  | 0777);
	// ppx->file[1] = open(ppx->argv[ppx->amount_cmds-1], O_RDWR | O_TRUNC | O_CREAT);//  | 0777);
    
    // checking if infile is correct
    if (ppx->file[1] < 0)
        error_msg("Failed to open file in second child!\n");
		
	// p[0] here is our read end, so we dont need the write end
	close(ppx->pipe[1]);
	
	// instead of outputting the result from our exeve in our terminal, we want it in file2(->outfile)
	dup2(ppx->file[1], STDOUT_FILENO);
	
	// and because the execve function needs something to read from we have to tell it, that the
	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
	// so we change stdin to the end of the pipe (p[0])
	dup2(ppx->pipe[0], STDIN_FILENO);


    // outfile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd gets attached at the end 
    outfile_path = get_path(ppx->envp, ppx->cmd);
    // printf("outfile peth: %s\n", outfile_path);
	
	

	// now we can execute the cmd1
	if(execve(outfile_path, ppx->cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in second child!\n");
}

void pipe_cmd(t_ppx *ppx, int32_t cmd_num)
{

	// handling very first cmd
	if (cmd_num == 1)
	{
	perror("cmd == 1");
		// printf("IN CMD == 1\n\n");
		// // if its the first cmd and there are only two
		// if (ppx->amount_cmds == 2)
		// 	ppx->file[1] = STDOUT_FILENO;
		// else // first command but there are more then 2 cmds
		// 	ppx->file[1] = open("tmp", O_RDWR | O_TRUNC | O_CREAT);
		handle_first_cmd(ppx);
	}
	// if its not the last cmd
	if (cmd_num != ppx->amount_cmds)
	{
	perror("cmd != last");
		// printf("IN CMD NOT LAST\n\n");
		handle_cmd(ppx);
	}
	else
	{
	perror("cmd == last");
		// printf("IN ELSE\n\n");
		// ppx->file[1] = 
		handle_last_cmd(ppx);
	}



	

}

void pipex(t_ppx *ppx)
{
	int32_t cmd_num = 1;
	int32_t child = 0;
	int32_t	cmd = 2;
	
	while (ppx->amount_cmds > cmd_num-1)
	{
		child = fork();
		if (child < 0)
			return (perror("Fork: "));
		// means its child -> should get killed at the end (beacuse of execve)
		if (child == 0)
		{
			printf("cdm: %d\n", cmd);
			ppx->cmd = ft_split(ppx->argv[cmd], ' ');
			printf("cmd[%d]: %s\n", cmd_num, ppx->cmd[0]);
			printf("cmd[%d]: %s\n", cmd_num, ppx->cmd[1]);
			printf("cmd[%d]: %s\n\n", cmd_num, ppx->cmd[2]);
			printf("amount cmds: %d\n", ppx->amount_cmds);
			pipe_cmd(ppx, cmd_num);
		}
		cmd++;
		cmd_num++;
	}
		waitpid(child, NULL, 0);
}

