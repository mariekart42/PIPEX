/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:31:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/09 21:20:55 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main()
{
    int id = fork();
    printf("he..llo\n\n");
    // if(id == 0)
    //     printf("we're in child process, ID: %d\n", id);
    // else
    //     printf("we're in main process, ID: %d\n", id);
    return(0);
}