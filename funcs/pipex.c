/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:20:25 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/30 15:26:28 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

/* function opens either 'infile' (as input from the terminal) or an 'tmp.hd' 
 * file if 'here_doc' is passed as an argument to the commandline
 * in both cases, function opens outfile, where the result of the commands
 * will be piped to */
void open_files(t_ppx *ppx)
{
	if (ppx->here_doc == false)
	{
		ppx->file[0] = open(ppx->av[1], O_RDONLY, 0666);
		if (ppx->file[0] < 0)
			error_msg("Failed to open infile!\n");
	}
	else
	{
		ppx->file[0] = open(".hd", O_TRUNC | O_CREAT | O_WRONLY, 0777);
		if (ppx->file[0] < 0)
			error_msg("Failed to open tmp.hd!\n");
	}
	ppx->file[1] = open(ppx->av[ppx->ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (ppx->file[1] < 0)
        error_msg("Failed to open outfile!\n");
}

/* if the here_doc action is called in the command line, function opens one pipe
 * if the here_doc action is NOT called in the command line, function opens as 
 * many pipes as command passed as an argument to the commandline minus one
 * also open_file function gets called to open in- and outfile (in both cases) */
void open_fds(t_ppx *ppx, int32_t pipes[MAX_FD][2])
{
	int32_t i;
	
	i = 0;
	if (ppx->here_doc == true)
	{
		if (pipe(pipes[0]) < 0)
			error_msg("Failed to open pipe\n");
	}
	else
	{
		while (i + 1 < ppx->amount_cmds)
		{
			if (pipe(pipes[i]) < 0)
				error_msg("Failed to open pipe\n");
			i++;
		}
	}
	open_files(ppx);
}

void	check_and_init_data(t_ppx *ppx, int32_t ac, char **av, char **envp)
{
	ppx->av = av;
	ppx->envp = envp;
	ppx->ac = ac;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		printf("its a heredoc!\n");
		if (ac < 6)
		{
			write(STDERR_FILENO, "invalid input! usage: ", 22);
			write(STDERR_FILENO, \
			"./pipex 'here_doc' <LIMITER> <cmd> ... <cmd> <outfile>\n", 56);
			exit(EXIT_FAILURE);
		}
		ppx->amount_cmds = 2;
		ppx->here_doc = true;
	}
	else
	{
		printf("its NOT a heredoc!\n");
		if (ac < 5)
		{
			write(STDERR_FILENO, "invalid input! usage: ", 22);
			write(STDERR_FILENO, \
			"./pipex <infile> <cmd> ... <cmd> <outfile>\n", 44);
			exit(EXIT_FAILURE);
		}
		ppx->amount_cmds = ac - 3;
		ppx->here_doc = false;
	}
}

/* function closes all open pipe-fds and the in- and outfile */
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

/* function gets the path from 'get_path' and executes the command */
void execute_cmd(t_ppx *ppx, int32_t cmd_num)
{
	char	*path;
	char	**cmd;

	if (ppx->here_doc == false)
		cmd = ft_split(ppx->av[cmd_num + 1], ' ');
	else
		cmd = ft_split(ppx->av[cmd_num + 2], ' ');
	path = get_path(ppx->envp, cmd);

	// now we can execute the cmd
	if (execve(path, cmd, ppx->envp) == -1)
		error_msg("Error: unable to execute execve() in first child!\n");
	free(path);
}

/* function redirects STDIN and STDOUT to either a file or a pipe
 * - for the first command, we get the input for the command not from STDIN_FILENO
 * 		but from our preinitialized infile (-> file[0])
 * - the last command gets redirected from STDOUT_FILENO to outfile (->file[0])
 * - otherwise the input from the command comes from the previoues write-end pipe
 *		and output gets redirected to the read-end from the next pipe
 *
 *		reads from
 *		  infile 
 *		 <-- <--   		[READ_END]   [WRITE_END]
 *		|       |		      ----------                   redirects
 *	infile     CHILD1 	   ->|	 PIPE   |<-		CHILD2 --> output to --> outfile
 *				   |	  |	  ----------  |       |         outfile
 *       		    --> -->                <-- <--
 *				   writes to		      reads from
 *				READ_END of pipe	   WRITE_END of pipe
 */
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
		printf("yes\n");
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
}
