/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:31:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/11 10:48:45 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "try.h"

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