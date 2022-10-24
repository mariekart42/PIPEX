/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:19:34 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/24 17:51:42 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// checking path:
// with "env | grep PATH" you get your current path
// eg.: PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
// now check validity for each part of the path (execve doesnt know where we are)
// eg. it could be path: "/usr/local/bin"
// if this is not valid we iterate through the next one and check for vality
// eg access("/usr/bin")
// if thats still not valid access("/bin") and so on
char    *get_path(char **envp)
{
	int     i;
	char	**splitted_path;
    char    *valid_path;
    
	i = 0;
	while (ft_strncmp(envp[i], "PATH=/", 6) != 0)
		i++;
	// iterate trough path and return path as soon as it is valid
    // +5 cause we dont want the "PATH=" but the first "/"
	splitted_path = ft_split(envp[i] + 5, ':');
    // printf("splitted_path[]: %s\n", splitted_path[0]);
    // printf("splitted_path[]: %s\n", splitted_path[1]);
    // printf("splitted_path[]: %s\n", splitted_path[2]);
    // printf("get path check\n");
	i = 0;
	while (access(splitted_path[i], F_OK | X_OK) != 0 && splitted_path != NULL)
		i++;
	if (splitted_path == NULL)
		error_msg("unable to find valid path\n");
    valid_path = malloc(ft_strlen(splitted_path[i]) + 1);
	valid_path = ft_strdup(splitted_path[i]);
	free_2d(splitted_path);
	if (valid_path == NULL)
		error_msg("unable to find valid path\n");
    return (valid_path);
}


// function attaches the first command in either **cmd_1
// or **cmd_2 at the end of the given path separated by a '/'
// character
char  *attach_cmd(char *valid_path, char **cmd)
{
	int32_t	i;
	int32_t	n;
	int32_t	cmd_len;
	char	*tmp_file;
	
	i = 0;
	n = 0;
	cmd_len = 0;
	// i is len of path
	while (valid_path[i] != '\0')
		i++;
    // printf("i: %d\n", i);
    // printf("valid path: %s\n", valid_path);
	// k is the len of the first argument
    // printf("cmd[0]: %s\n", cmd[0]);
	cmd_len = ft_strlen(cmd[0]);
    // printf("check att cmd\n");
    // printf("k: %d\n", k);
	tmp_file = malloc(i + cmd_len + 1);
	while (valid_path[n] != '\0')
	{
		tmp_file[n] = valid_path[n];
		n++;
	}
	i = 0;
	tmp_file[n++] = '/';
    // printf("tmp: %s\n", tmp_file);
	while (cmd_len >= i)
	{
        // printf("cmd_len: %d, i: %d\n\n", cmd_len, i);
		tmp_file[n] = cmd[0][i];
		i++;
		n++;
        // printf("n: %d\n", n);
	}
	tmp_file[n] = '\0';
    // printf("tmp_file: %s\n", tmp_file);
    free(valid_path);
	if (tmp_file == NULL)
		error_msg("unable to create path\n");
	return (tmp_file);
}
