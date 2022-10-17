/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/17 15:36:21 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		id;
	int		p[2];
	char	buff[20];
	// len of argv[2]
	int32_t len_argv_2 = strlen(argv[1]);
	// printf("len of argv[1]: %lu\n", strlen(argv[1]));
	printf("argv[]: %s\n", argv[0]);
	printf("argv[]: %s\n", argv[1]);
	printf("argv[]: %s\n\n", argv[2]);
	printf("argv[]: %s\n\n", envp[3]);
	// char *args[]     = { "ls", "-l", "-a", NULL };
    // char *env_args[] = { "PATH=/bin", "USER=me", NULL };

    execve("/usr/local/bin", argv++, envp);
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
