/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:11:31 by mmensing          #+#    #+#             */
/*   Updated: 2022/10/11 18:07:11 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "try.h"

// execve executes a programm and returns in case of success nothing
// -> execve on forked process

int main(int argc, char *argv[], char *const envp[])
{
    char *vecs[] = {"ls", "wc", NULL};
    if(execve("./file",argv, vecs) < 0)
        printf("rerrorrrr\n");
    printf("yee\n");
}



// gcc try_execute.c -o try_execute
// gcc file.c -o file
// ./try_execute

// -> prints the stuff in file.c but not "yee"


// file.c:

// #include <stdio.h>

// int main(int argc, char *argv[], char *envp[])
// {
//     printf("INN FILA\n");
//     printf("argv: %s\n", argv[0]);
//     printf("argv: %s\n", argv[1]);
//     printf("argv: %s\n", argv[2]);
//     printf("argv: %s\n", argv[3]);
//     printf("argv: %s\n", argv[4]);
//     printf("\nnow envp:\n");
//     printf("envp: %s\n", envp[0]);
//     printf("envp: %s\n", envp[1]);
//     printf("envp: %s\n", envp[2]);
// }