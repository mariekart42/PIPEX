/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:00:29 by mmensing          #+#    #+#             */
/*   Updated: 2022/12/02 15:41:47 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void here_doc(t_ppx *ppx, int32_t pipe[MAX_FD][2])
{
	char	*buff;
	int32_t	tmp_fd;
	
	tmp_fd = open("tmp.hd", O_TRUNC | O_CREAT | O_WRONLY);
	printf("tmp fd: %d\n", ppx->file[0]);
	// as long we dont hit delimiter
	while (1)
	{
		write(1, "heredoc> ", 9);
		buff = get_next_line(STDIN_FILENO);
		// printf("in: %s\n", buff);
		if (ft_strncmp(ppx->av[2], buff, ft_strlen(ppx->av[2])) == 0)
			break ;
		write(tmp_fd, &buff, ft_strlen(buff));
		free(buff);
	}
	// ppx->file[0] = tmp_fd;
	close(tmp_fd);
	close_fds(ppx, pipe);
	
	printf("lines: %s\n", get_next_line(tmp_fd));
	printf("lines: %s\n", get_next_line(tmp_fd));
	printf("lines: %s\n", get_next_line(tmp_fd));
}

