/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/24 17:14:32 by mmensing         ###   ########.fr       */
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



	// int32_t	outfile;
	
	// // outfile we need read and write, gets created if it doesnt exist,
	// // O_TRUNC -> if it exist, lengh will get truncated to 0
	// // 0644 -> not really sure, delete in the end if not needed
	// outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	// if (outfile < 0)
	// {
	// 	perror("open outfile: ");
	// 	return (-1);
	// }
	
	
	return (0);
}

