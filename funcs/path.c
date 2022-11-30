/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:19:34 by mmensing          #+#    #+#             */
/*   Updated: 2022/11/30 13:25:45 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

/* checking path:
 * with "env | grep PATH" you get your current path
 * eg.: PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki
 * now check validity for each part of the path
 * eg. it could be path: "/usr/local/bin"
 * if this is not valid we iterate through the next one and check for vality
 * eg access("/usr/bin")
 * if thats still not valid access("/bin") and so on */
char *get_path(char **envp, char **cmd)
{
	int     i;
	int		k;
	char	**splitted_path;
    char    *valid_path;

	i = 0;
	k = 0;
	while (ft_strncmp(envp[i], "PATH=/", 6) != 0)
		i++;
		
	// iterate trough path and return path as soon as it is valid
    // +5 cause we dont want the "PATH=" but the first "/"
	splitted_path = ft_split(envp[i] + 5, ':');
	while (splitted_path[k] != NULL)
	{
		splitted_path[k] = ft_strjoin(splitted_path[k], "/");

		valid_path = ft_strjoin(splitted_path[k], cmd[0]);

		if (access(valid_path, F_OK | X_OK) == 0)
			break;
		free(valid_path);
		k++;
	}
	if (access(valid_path, F_OK | X_OK) != 0)
		error_msg("unable to find valid path!\n");
		
	if (*splitted_path)
		free(*splitted_path);
	if (splitted_path)
		free(splitted_path);
		
	return (valid_path);
}
