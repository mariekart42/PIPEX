/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/21 11:43:36 by mmensing         ###   ########.fr       */
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

void attach_cmd(t_path *x)
{
	int i = 0;
	while (x->path[i] != '\0')
		i++;
	ft_strlen()
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
	// at the end always append the first argument of the command 
	// eg if arg[0] = "ls", => access("/bin/ls");
void get_path(char **envp, t_path *x)
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
	attach_cmd(x);
}


int	main(int argc, char **argv, char **envp)
{
	// int		id;
	// int		p[2];
	// char	buff[20];
	// char	*args;
	argc++;
	t_path	x;
	
	// assigning all commands of argv[2] into 2d array
	x.cmd_1 = ft_split(argv[2], ' ');
	
	// function assigns accessable path from envp to x.path of t_path struct
	// also assigns first command at the end
	get_path(envp, &x);
	
	
	assign_first_cmd(argv, &x);
	// execle(x.path, )
	exit (0);
	

	
	// char *args[]     = {"ls", "-l", "-a", NULL };
    // char *env_args[] = { envp[5], envp[3], NULL };
	// char* arr[] = {"ls", NULL};
	// while(*envp)
	// {
	// 	if(ft_strncmp(*envp, "HOME", 4) == 0)
	// 		printf("YES envp[]: %s\n", *envp);
	// 	else
	// 		printf("... no, argv: %s\n", *envp);
	// 	envp++;
	// }
	// env = { "HOME=/root", "PATH=/bin:/sbin", NULL }
	

	// strerror()
	// perror("dumm");
	
	printf("printf permission: %d\n\n", access("/usr/bin/ls", F_OK | X_OK));
	
	// array that you pass to the execve has only the argumentes you want to execute
	// bsp arg[0] = ls, arg[1] = -l, arg[2] = NULL
	// same thing for the second arg array i guess
	
	

	
	// search_path()
	
	execv("/bin/ls", argv+1);
    // execve("usr/local/bin/ls", argv, envp);
    fprintf(stderr, "Oops!\n");

	// if (pipe(p) < 0)
	// 	exit (1);
	// id = fork();
	// if (id > 0)
	// {
	// 	printf("here speaks your parent\nID: %d\n", id);
	// 	// writing lol into the pipe
	// 	write(p[1], argv[1], len_argv_2 + 1);
	// 	// write(2, argv[1], 10);
	// 	// wait(NULL); // dunno about this
	// }
	// else
	// {
	// 	printf("\n\nhere speakes your child\nID: %d\n", id);
	// 	// reading from the pipe
	// 	read(p[0], buff, len_argv_2 + 1);
	// 	printf("printing from pipe: %s\n", buff);
	// }
}
