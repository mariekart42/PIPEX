/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:18:00 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/25 13:38:12 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

// libft
# include "../libs/LIBFT/libft.h"

# include <stdbool.h> // bool stuff
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>

// defines macros for exit func (EXIT_SUCCESS and EXIT_FAILURE)
# include <stdlib.h>

// strerror
# include <string.h>

// perror handling
#include <errno.h> 

// open function
#include <sys/stat.h>
#include <fcntl.h>


//		ERROR.C
void	error_msg(char *msg);
void check_input(int argc);


//		EXTRA_FUNCS.C
void free_2d(char **array);


//		PATH.C
char *get_path(char **envp, char **cmd);


//		PIPEX.C
void pipex(int32_t file[], int32_t pipe[], char **argv, char **envp);
void	second_process(int32_t file[], int32_t pipe[], char **envp, char **argv);
void	first_process(int32_t file[], int32_t pipe[], char **envp, char **argv);

#endif
