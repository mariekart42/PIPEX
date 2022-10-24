/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:18:00 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/24 17:26:01 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H



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

typedef struct	s_path
{
	// // fd of both files
	// int32_t	infile;
	// int32_t	outfile;
	
	// // read and write end of pipe
	// int32_t	p[2];
	
	// char	*valid_path;
	// char	*infile_path;
	// char	*outfile_path;
	// char	**cmd_1;
	// char	**cmd_2;
	// char	**my_envp;
	int32_t	my_argc;
	struct s_list *next;
}				t_path;


//		ERROR.C
void	error_msg(char *msg);
void check_input(int argc);


//		EXTRA_FUNCS.C
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void free_2d(char **array);
char	*ft_strdup(char *src);

//		PATH.C
char    *get_path(char **envp);
char  *attach_cmd(char *valid_path, char **cmd);


//		PIPEX.C
void pipex(int32_t file[], int32_t pipe[], char **argv, char **envp);
void	second_process(int32_t file[], int32_t pipe[], char **envp, char **argv);
void	first_process(int32_t file[], int32_t pipe[], char **envp, char **argv);


//	INCLUDE LATER LIBFT
//		FT_SPLIT.C
char	*sub_dup(const char *str, int32_t start, int32_t finish);
int	amount_subs(const char *s, char c);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);

#endif

