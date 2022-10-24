/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:07:55 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/24 17:19:42 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(int file[], int pipe[], char **envp, char **argv)
{
    char    *infile_path;
    char    **cmd_1 = NULL;

    // 2d array of all commands + NULL-terminated
    cmd_1 = ft_split(argv[2], ' ');
    // printf("cmd: %s\n", cmd_1[0]);
    // printf("cmd: %s\n", cmd_1[1]);
    // printf("cmd: %s\n", cmd_1[2]);
    // infile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd_1 gets attached at the end 
    
    infile_path = attach_cmd(get_path(envp), cmd_1);
    // printf("infile peth: %s\n", infile_path);
    
    // open infile we only need to read from
	file[0] = open(argv[1], O_RDONLY);
    
    // checking if infile is correct
    if (file[0] < 0)
        error_msg("Failed to open file!\n");


	// p[1] here is our write end, so we dont need the read end
	close(pipe[0]);
    
	// printf("infile path: %s\n", infile_path);
	// printf("cmd[]: %s\n", cmd_1[0]);
	// printf("cmd[]: %s\n", cmd_1[1]);
	// printf("cmd[]: %s\n", cmd_1[2]);
	// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
	// for this we redirect stdin to infile
	dup2(file[0], STDIN_FILENO);
	
	// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
	// the output to writing end of our pipe (p[1])
	dup2(pipe[1], STDOUT_FILENO);
    
	// now we can execute the cmd1
	execve(infile_path, cmd_1, envp);

}

// void	second_process(int file[], int p[], char **envp, char **argv)
// {
	
// 	// p[0] here is our read end, so we dont need the write end
// 	close(p[1]);
	
// 	// instead of outputting the result from our exeve in our terminal, we want it in file2(->outfile)
// 	dup2(outfile, STDOUT_FILENO);
	
// 	// and because the execve function needs something to read from we have to tell it, that the
// 	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
// 	// so we change stdin to the end of the pipe (p[0])
// 	dup2(p[0], STDIN_FILENO);
	
// 	// now we have to find the valid path ('again' cause child 2 doesnt know anything whats happening in child1 
// 	//  (or can we wait for child1 and the stuff will be in our struct?) -> doing this now)
// 	x->outfile_path = attach_cmd(x->valid_path, x->cmd_2);
// 	printf("infile_path: %s\n",x->outfile_path);
// 	// in the end find args and do execve -> args in cmd2
// 	execve(x->outfile_path, x->cmd_2, x->my_envp);
// }

void pipex(int file[], int pipe[], char **argv, char **envp)
{
	int32_t	child[2];
	

	// FORK first child
	child[0] = fork();
	if (child[0] < 0)
		return (perror("Fork: "));
	if (child[0] == 0)
		first_process(file, pipe, envp, argv);
    
	waitpid(child[0], NULL, 0); // waiting till first child finished
    // printf("check\n");
    // // FORK second child
	// child[1] = fork();
	// if (child[1] < 0)
	// 	return (perror("Fork: "));
	// if (child[1] == 0)
	// 	second_process(outfile, p, x);
	
	close(pipe[0]);
	close(pipe[1]);
	
    // waitpid(child[1], &status, 0);


	exit (0);

}