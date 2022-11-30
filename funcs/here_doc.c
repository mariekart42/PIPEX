/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:00:29 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/29 15:30:29 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

void here_doc(t_ppx *ppx)
{
	char	*buff;
	int32_t	tmp_fd;
	
	tmp_fd = open("tmp.hd", O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	// as long we dont hit delimiter
	while (1)
	{
		write(1, "heredoc> ", 9);
		buff = get_next_line(STDIN_FILENO);
		if (ft_strncmp(ppx->av[2], buff, ft_strlen(ppx->av[2])) == 0)
			break ;
		write(tmp_fd, &buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(tmp_fd);
}

