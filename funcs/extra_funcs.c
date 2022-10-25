/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:54:08 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/25 13:36:48 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/pipex.h"

// function frees 2d array
void free_2d(char **array)
{	
	int n;
	int i;
	
	n = 0;
	i = 0;
	while (array[n] != NULL)
		n++;
	while (i < n)
	{
    	free(array[i]);
		i++;
	}
	free(array);
}
