/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/25 13:01:21 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_ppx	ppx;
	
	check_input(argc);
	ppx.argv = argv;
	ppx.envp = envp;
	count_commands(&ppx, argc);
	pipex(&ppx);


	// // creating pipe:
	// // p[0] is the reading end, so the parent cause it needs to read the passed 
	// //	command from the child to execute it
	// // p[1] is the writing end, so the cild writes to the parent the command
	// //	that the parent needs to execute
	// if (pipe(ppx.pipe) < 0)
	// 	error_msg("failed to open pipe!\n");





	
	
	return (0);
}

