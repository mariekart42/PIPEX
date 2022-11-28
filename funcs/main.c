/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/28 21:00:07 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

int	main(int ac, char *av[], char **envp)
{
	t_ppx	ppx;
	int32_t	pipes[MAX_FD][2];

	check_and_init_data(&ppx, ac, av, envp);
	open_files(&ppx, ac);
	open_pipes(&ppx, pipes);
	pipex(&ppx, pipes);
	return (0);
}
