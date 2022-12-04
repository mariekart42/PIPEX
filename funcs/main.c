/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/04 23:22:53 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

int	main(int ac, char *av[], char **envp)
{
	t_ppx	ppx;
	int32_t	pipes[MAX_FD][2];
	ppx.status = true;

	check_and_init_data(&ppx, ac, av, envp);
	open_fds(&ppx, pipes);
	// printf("\nmain\npipes:\n1. %d\n2. %d\n3. %d\n4. %d\n\n", pipes[0][0], pipes[0][1], pipes[1][0], pipes[1][1]);
	// printf("files: \n1. %d\n2. %d\n\n", ppx.file[0], ppx.file[1]);
	if (ppx.here_doc == true)
		here_doc(&ppx, pipes);
		
	// printf("text: %s\n", get_next_line(ppx.file[0]));
	// printf("text: %s\n", get_next_line(ppx.file[1]));
	// printf("text: %s\n", get_next_line(ppx.file[2]));
	pipex(&ppx, pipes);
	close_fds(&ppx, pipes);
	return (WEXITSTATUS(ppx.status));
	// exit(ppx.status[0]);
}
