/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:18:00 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/27 13:30:41 by mmensing         ###   ########.fr       */
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


#define MAX_FD 1024

typedef struct s_ppx
{
	int32_t pipe[2];
	int32_t file[2];
	int32_t next_file;
	int32_t amount_cmds;
	char	**envp;
	char	**av;
	// char	**cmd;
	int32_t save_prev_pipe_end;
	// int32_t	prev_;
	// char	*outfile_path;
	
}				t_ppx;

//		ERROR.C
void	error_msg(char *msg);
void check_input(int ac);


//		EXTRA_FUNCS.C
void free_2d(char **array);


//		PATH.C
char *get_path(char **envp, char **cmd);


//		PIPEX.C
// void pipex(int32_t file[], int32_t pipe[], char **argv, char **envp);
// void	second_process(int32_t file[], int32_t pipe[], char **envp, char **argv);
// void	first_process(int32_t file[], int32_t pipe[], char **envp, char **argv);

// //		bonus.c
// void execute_cmd(t_ppx *ppx, int32_t cmd_num, char **cmd);
// void pipex(t_ppx *ppx);
// void count_commands(t_ppx *ppx, int32_t argc);
// void open_files(t_ppx *ppx, int32_t ac);

//		pipex.c
void open_files(t_ppx *ppx, int32_t ac);
void open_pipes(t_ppx *ppx, int32_t pipes[MAX_FD][2]);
void count_commands(t_ppx *ppx, int32_t argc);



#endif

