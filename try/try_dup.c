/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:19:35 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/11 18:29:53 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "try.h"

// dup creates a new filedescriptor for the same file
// -> two different filedescriptors pointing to the same file
//
// fd_b = dup(fd_a);
//
// fd_a = 3 ---------> file.c
//                       ^
// fd_b = 4 _____________|
// 

// dup2() in addition specifis which filedescriptor the file should have now
// we are able to actually change eg stdout now
// -> instead printing stuff on the terminal, it will print the stuff into the file

int main(int argc, char *argv[], char *envp[])
{
    
}