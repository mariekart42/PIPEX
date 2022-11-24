/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:17:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/24 16:38:15 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_ppx	ppx;
	
	check_input(argc);
	envp++;
	// argv++;
	count_commands(&ppx, argc);
	
	printf("amount cmds: %d\n", ppx.amount_cmds);
		
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);
	printf("argv[2]: %s\n", argv[2]);
	printf("argv[3]: %s\n", argv[3]);
	printf("argv[4]: %s\n", argv[4]);
	printf("argv[5]: %s\n", argv[5]);

	// // creating pipe:
	// // p[0] is the reading end, so the parent cause it needs to read the passed 
	// //	command from the child to execute it
	// // p[1] is the writing end, so the cild writes to the parent the command
	// //	that the parent needs to execute
	// if (pipe(data.pipe) < 0)
	// 	error_msg("failed to open pipe!\n");

	// pipex(&data, argv, envp);




	
	
	return (0);
}

