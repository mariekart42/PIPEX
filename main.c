/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/18 11:28:53 by mmensing         ###   ########.fr       */
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
		{
			return ((unsigned char)(s1[i]) - ((unsigned char)s2[i]));
		}
	i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		id;
	int		p[2];
	char	buff[20];
	// len of argv[2]
	// int32_t len_argv_2 = strlen(argv[1]);
	// // printf("len of argv[1]: %lu\n", strlen(argv[1]));
	// printf("argv[]: %s\n", argv[0]);
	// printf("argv[]: %s\n", argv[1]);
	// printf("argv[]: %s\n\n", argv[2]);
	// printf("argv[5]: %s\n\n", envp[5]);
	// printf("argv[3]: %s\n\n", envp[3]);
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
	printf("printf permission: %d\n\n",access("/usr/local/bin/", R_OK));
	execv("/Users/mmensing/Desktop/42/PIPEX/ls", argv+2);
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
