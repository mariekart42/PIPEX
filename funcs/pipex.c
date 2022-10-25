/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 13:07:55 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/25 13:26:32 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void	first_process(int32_t file[], int32_t pipe[], char **envp, char **argv)
{
    char    *infile_path;
    char    **cmd_1 = NULL;

    
    // open outfile we need to:
	// O_RDONLY	-> read only
	// 0644		-> files owner can read and write, the others only read
	file[0] = open(argv[1], O_RDONLY | 0644);
    
    // checking if infile is correct
    if (file[0] < 0)
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
    // printf("infile peth: %s\n", infile_path);
	
	


	// now we can execute the cmd1
	if (execve(infile_path, cmd_1, envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(infile_path);
}

void	second_process(int32_t file[], int32_t pipe[], char **envp, char **argv)
{
	char    *outfile_path;
    char    **cmd_2 = NULL;
	
    // open outfile we need to:
	// O_RDWR	-> read and write
	// O_CREAT	-> create if it doesn't exist
	// O_TRUNC	-> len always truncated to 0
	// 0777		-> full access lol
	file[1] = open(argv[4], O_RDWR | O_TRUNC | O_CREAT);//  | 0777);
    
    // checking if infile is correct
    if (file[1] < 0)
        error_msg("Failed to open file in second child!\n");
		
	// p[0] here is our read end, so we dont need the write end
	close(pipe[1]);
	
	// instead of outputting the result from our exeve in our terminal, we want it in file2(->outfile)
	dup2(file[1], STDOUT_FILENO);
	
	// and because the execve function needs something to read from we have to tell it, that the
	// reading stuff is not in the terminal but at the end of the pipe that we created in child1
	// so we change stdin to the end of the pipe (p[0])
	dup2(pipe[0], STDIN_FILENO);
	
	// 2d array of all commands + NULL-terminated
    cmd_2 = ft_split(argv[3], ' ');

    // outfile path is a valid path that get figured out in 'get_path'
    // and then the first command in cmd_2 gets attached at the end 
    outfile_path = get_path(envp, cmd_2);
    // printf("outfile peth: %s\n", outfile_path);
	
	

	// now we can execute the cmd1
	if(execve(outfile_path, cmd_2, envp) == -1)
		error_msg("Error: unable to execute execve() in second child!\n");
}

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
    // FORK second child
	child[1] = fork();
	if (child[1] < 0)
		return (perror("Fork: "));
	if (child[1] == 0)
		second_process(file, pipe, envp, argv);
	
	close(pipe[0]);
	close(pipe[1]);
	
    waitpid(child[1], NULL, 0);

    // printf("check\n");

	// exit (0);

}