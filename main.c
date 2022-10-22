/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/22 15:51:36 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
compares 2 char arrays if one of them is greater, less or equal
stop point is a fixed variable n
for extendet ascii using unsigned char
e.g. 
"abc" > "aba"   ->    returns 1
  ""  =  ""     ->    returns 0
 "a"  < "abc"   ->    returns -1
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - ((unsigned char)s2[i]));
	i++;
	}
	return (0);
}

// function attaches the first command in either **cmd_1
// or **cmd_2 at the end of the given path separated by a '/'
// character
char  *attach_cmd(t_path *x, char *cmd)
{
	int32_t	i;
	int32_t	n;
	int32_t	k;
	char	*tmp_file;
	
	i = 0;
	n = 0;
	k = 0;
	// i is len of path
	while (x->path[i] != '\0')
		i++;
	// k is the len of the first argument
	while (cmd[k] != '\0')
		k++;
	tmp_file = malloc(i + k + 1);
	while (x->path[n] != '\0')
	{
		tmp_file[n] = x->path[n];
		n++;
	}
	i = 0;
	tmp_file[n++] = '/';
	while (cmd[i] != '\0')
	{
		tmp_file[n] = cmd[i];
		i++;
		n++;
	}
	tmp_file[n] = '\0';
	free(x->path);
	return (tmp_file);
}

// function frees 2d array
void free_2d(char **array)
{	
	int n;
	int i;
	
	n = 0;
	i = 0;
	while (array[n] != NULL)
		n++;
	while (i < n)
	{
    	free(array[i]);
		i++;
	}
	free(array);
}


	// checking path:
	// with "env | grep PATH" you get your current path
	// eg.: PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
	// now check validity for each part of the path (execve doesnt know where we are)
	// eg. it could be path: "/usr/local/bin"
	// if this is not valid we iterate through the next one and check for vality
	// eg access("/usr/bin")
	// if thats still not valid access("/bin") and so on
void get_path(char **envp, t_path *x, ...)
{
	int	i;
	char	**splitted_path;
	i = 0;
	while (ft_strncmp(envp[i], "PATH=/", 6) != 0)
		i++;
	// printf("env[%i]: %s\n",i, envp[i]);
	
	// iterate trough path and return path as soon as it is valid
	splitted_path = ft_split(envp[i], ':');
	i = 0;
	while (access(splitted_path[i], F_OK | X_OK) != 0)
		i++;
	// printf("path: %s\n", splitted_path[i]);
	x->path = splitted_path[i];
	free_2d(splitted_path);
}
ft_printf(char* t, ...);
printf("%d %d", int, int);

int	main(int argc, char **argv, char **envp)
{
	int infile;
	int outfile;
	// open both files
	// infile we only need to read from
	infile = open(ag[1], O_RDONLY);
	// outfile we need read and write, gets created if it doesnt exist,
	// O_TRUNC -> if it exist, lengh will get truncated to 0
	// 0644 -> not really sure, delete in the end if not needed
	outfile = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
	{
		perror("open files: ");
		return (-1);
	}
	int32_t p[2];
	int		id;
	argc++;
	t_path	x;
	
	// creating pipe:
	// p[0] is the reading end, so the parent cause it needs to read the passed 
	//	command from the child to execute it
	// p[1] is the writing end, so the cild writes to the parent the command
	//	that the parent needs to execute
	pipe(p);
	
	
	//	BEFORE FORK

	
	// function assigns accessable path from envp to x.path of t_path struct
	get_path(envp, &x);
	
	// printf("argv[3]: %s\n", argv[3]);
	// FORK:
	id = fork();
	
	// PARENT
	if (id != 0)
	{
		// assigning all commands of argv[3] into 2d array cmd_2
		(*x).cmd_2 = ft_split(argv[3], ' ');
		
		// attach first argument to the end of path
		(*x).infile_path = attach_cmd(&x, (*x).cmd_1);

	}
	// CHILD
	if (id == 0)
	{
	//	FIRST CHILD
		// we execute the command not 'on' the stuff in the terminal, but on file1 (->infile)
		// for this we redirect stdin to infile
		// -> dup2(infile, stdin);
		// instead of printing the output of the first cmd now to the terminal (stdout), we redirect (via fd)
		// the output to file2 (->outfile)
		// -> dup2(p[1], stdout);
		// p[1] here is our write end, so we dont need the read end
		// -> close(p[0]);
		// now we can execute the cmd1
		// -> find valid path
		// -> create argument_list
		// execve(valid_path, argument_list, envp);
	
	//	SECOND CHILD
		// instead of outputting the result from our exeve in our terminal, we want it in file2(->outfile)
		// -> dup2(outfile, stdout);
		// and because the execve function needs something to read from we have to tell it, that the
		// reading stuff is not in the terminal but at the end of the pipe that we created in child1
		// so we change stdin to the end of the pipe (p[0])
		// -> dup2(p[0], stdin);
		// now we have to find the valid path ('again' cause child 2 doesnt know anything whats happening in child1 
		//  (or can we wait for child1 and the stuff will be in our struct?))
		// in the end find args and do execve

	}
	
	exit (0);

}
