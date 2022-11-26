/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:16:54 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/26 16:30:00 by mmensing         ###   ########.fr       */
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

// void handle_cmd(t_ppx *ppx)
// {
// 	char    *path;
//     // char    **cmd_2 = NULL;
	
// 	// file[1] is a temporary file that needs to be deleted in the end
// 	ppx->file[1] = open("tmp", O_RDONLY | 0644);
    
//     // checking if infile is correct
//     if (ppx->file[1] < 0)
//         error_msg("Failed to open file in second child!\n");
		
// 	// p[0] here is our read end, so we dont need the write end
// 	close(ppx->pipe[1]);
	
// 	// instead of outputting the result from our exeve in our terminal, we want it in file2
// 	dup2(ppx->file[1], STDOUT_FILENO);
	
// 	// and because the execve function needs something to read from we have to tell it, that the
// 	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
// 	// so we change stdin to the end of the pipe (p[0])
// 	dup2(ppx->pipe[0], STDIN_FILENO);

//     // path is a valid path that get figured out in 'get_path'
//     // and then the first command in cmd gets attached at the end 
//     path = get_path(ppx->envp, ppx->cmd);
//     // printf("outfile peth: %s\n", outfile_path);
	
	

// 	// now we can execute the cmd1
// 	if(execve(path, ppx->cmd, ppx->envp) == -1)
// 		error_msg("Error: unable to execute execve() in second child!\n");
// 	free(path);
// }

// void handle_first_cmd(t_ppx *ppx)
// {
// 	char    *infile_path;

//     // open outfile we need to:
// 	// O_RDONLY	-> read only
// 	// 0644		-> files owner can read and write, the others only read
// 	ppx->file[0] = open(ppx->argv[1], O_RDONLY | 0644);
    
//     // checking if infile is correct
//     if (ppx->file[0] < 0)
//         error_msg("Failed to open file in first process!\n");

// 	// p[1] here is our write end, so we dont need the read end
// 	close(ppx->pipe[0]);
	
	

// 	// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
// 	// for this we redirect stdin to infile
// 	dup2(ppx->file[0], STDIN_FILENO);
	
// 	// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
// 	// the output to writing end of our pipe (p[1])
// 	dup2(ppx->pipe[1], STDOUT_FILENO);
	
//     // infile path is a valid path that get figured out in 'get_path'
//     // and then the first command in cmd gets attached at the end 
//     infile_path = get_path(ppx->envp, ppx->cmd);

// 	// now we can execute the cmd
// 	if (execve(infile_path, ppx->cmd, ppx->envp) == -1)
// 		error_msg("Error: unable to execute execve() in first child!\n");
// 	free(infile_path);
// }

// void handle_last_cmd(t_ppx *ppx)
// {
// 	char    *outfile_path;
//     // char    **cmd_2 = NULL;
	
//     // open outfile we need to:
// 	// O_RDWR	-> read and write
// 	// O_CREAT	-> create if it doesn't exist
// 	// O_TRUNC	-> len always truncated to 0
// 	// 0777		-> full access lol
// 	ppx->file[1] = open("OUTFILE_", O_RDWR | O_TRUNC | O_CREAT);//  | 0777);
// 	// ppx->file[1] = open(ppx->argv[ppx->amount_cmds-1], O_RDWR | O_TRUNC | O_CREAT);//  | 0777);
    
//     // checking if infile is correct
//     if (ppx->file[1] < 0)
//         error_msg("Failed to open file in second child!\n");
		
// 	// p[0] here is our read end, so we dont need the write end
// 	close(ppx->pipe[1]);
	
// 	// instead of outputting the result from our exeve in our terminal, we want it in file2(->outfile)
// 	dup2(ppx->file[1], STDOUT_FILENO);
	
// 	// and because the execve function needs something to read from we have to tell it, that the
// 	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
// 	// so we change stdin to the end of the pipe (p[0])
// 	dup2(ppx->pipe[0], STDIN_FILENO);


//     // outfile path is a valid path that get figured out in 'get_path'
//     // and then the first command in cmd gets attached at the end 
//     outfile_path = get_path(ppx->envp, ppx->cmd);
//     // printf("outfile peth: %s\n", outfile_path);
	
	

// 	// now we can execute the cmd1
// 	if(execve(outfile_path, ppx->cmd, ppx->envp) == -1)
// 		error_msg("Error: unable to execute execve() in second child!\n");
// }


void execute_cmd(t_ppx *ppx, int32_t cmd_num)
{
	char	*cmd_path;
	
	// p[1] here is our write end, so we dont need the read end
	// close(ppx->pipe[0]);
	// close(ppx->prev_[0]);
	
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
	// -> except for the last cmd, ther we redirect the writing end to the outfile (-2 cause cmd_num starts from 0)
	if (ppx->amount_cmds == cmd_num)
		dup2(ppx->file[1], STDOUT_FILENO);
	else
	{
		dup2(ppx->pipe[1], STDOUT_FILENO);
		// ppx->prev_ = ppx->pipe[0];
	}
		
	
	// outfile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd gets attached at the end 
    cmd_path = get_path(ppx->envp, ppx->cmd);
	
	// now we can execute the cmd
	if (execve(cmd_path, ppx->cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in second child!\n");
}

// void redirect(t_ppx *ppx, int32_t cmd_num)
// {
// 	// if very first cmd read end from pipe needs to be infile -> already did this in open_file
// 	// otherwise the write end from the prev pipe
// 	if (cmd_num == 0)
// 	{
// 		execute_cmd(ppx, cmd_num);
// 	}
// 	else
// 	{
// 	}
// }

void pipex(t_ppx *ppx)
{
	int32_t cmd_num = 1;
	int32_t pid = 0;
	
	
	// if (pipe(ppx->prev_) < 0)
	// 	error_msg("failed to open pipe!\n");
	while (cmd_num <= ppx->amount_cmds)
	{
		printf("cmd_num: %d\n", cmd_num);
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
			// redirect(ppx, cmd_num);
			execute_cmd(ppx, cmd_num);
		}
		cmd_num++;
		waitpid(pid, NULL, 0);
	}
	close(ppx->file[0]);
	close(ppx->file[1]);
}