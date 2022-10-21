/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:18:00 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/21 11:45:39 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

typedef struct	s_path
{
	char	*path;
	char	**cmd_1;
	char	**cmd_2;
	struct s_list *next;
}				t_path;

# include <ctype.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stddef.h>
# include <stdint.h>

void get_path(char **envp, t_path *x);

//		ft_split.c
static char	*sub_dup(const char *str, int start, int finish);
static int	amount_subs(const char *s, char c);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);

//		main.c
void free_2d(char **array);
void get_path(char **envp, t_path *x);
void attach_cmd(t_path *x);


#endif

