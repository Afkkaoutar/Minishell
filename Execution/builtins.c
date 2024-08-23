/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 01:58:06 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/08/23 02:04:38 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void my_echo(char **args) 
{
    int newline = 1; 
    int i = 1;

    if (args[1] && ft_strcmp(args[1], "-n") == 0) 
    {
        newline = 0; 
        i = 2;
    }

    for (; args[i] != NULL; i++) 
    {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) 
        {
            printf(" ");
        }
    }

    if (newline) 
    {
        printf("\n");
    }
}


void my_cd(char **args) 
{
    if (args[1] == NULL) 
    {
        fprintf(stderr, "cd: expected argument\n");
    }
    else
    {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

void my_pwd() 
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("%s\n", cwd);
    }
    else 
    {
        perror("pwd");
    }
}



