/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/24 23:10:04 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	int32_t	file[2];
	int32_t	pipe_[2];
	
	check_input(argc);
	
	// creating pipe:
	// p[0] is the reading end, so the parent cause it needs to read the passed 
	//	command from the child to execute it
	// p[1] is the writing end, so the cild writes to the parent the command
	//	that the parent needs to execute
	if (pipe(pipe_) < 0)
		error_msg("failed to open pipe!\n");

	pipex(file, pipe_, argv, envp);




	
	
	return (0);
}

