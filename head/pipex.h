/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:18:00 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/30 13:02:13 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

// for get_next_line
# define BUFFER_SIZE 1

// libft
# include "../include/libft/libft.h"

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
# include <errno.h> 

// open function
# include <sys/stat.h>
# include <fcntl.h>


#define MAX_FD 1024

typedef struct s_ppx
{
	int32_t file[2];
	int32_t amount_cmds;
	char	**envp;
	char	**av;
	int32_t	ac;
	bool	here_doc;
}				t_ppx;

//		../include/get_next_line/get_next_line.c
void	buff_after_line(char *buff);
char	*create_last(char *buff, char *line);
char	*get_next_line(int fd);


//		ERROR.C
void	error_msg(char *msg);


//		EXTRA_FUNCS.C
void free_2d(char **array);


//		PATH.C
char *get_path(char **envp, char **cmd);


//		../funcs/pipex.c
void open_files(t_ppx *ppx);
void open_fds(t_ppx *ppx, int32_t pipes[MAX_FD][2]);
void	check_and_init_data(t_ppx *ppx, int32_t ac, char **av, char **envp);
void close_fds(t_ppx *ppx, int32_t pipes[MAX_FD][2]);
void execute_cmd(t_ppx *ppx, int32_t cmd_num);
void redirect(t_ppx *ppx, int32_t pipes[MAX_FD][2], int32_t i);
void pipex(t_ppx *ppx, int32_t pipes[MAX_FD][2]);


//		../funcs/here_doc.c
void here_doc(t_ppx *ppx);


#endif

