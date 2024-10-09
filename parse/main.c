/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 00:25:05 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/09 19:20:40 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	s()
// {
// 	system("leaks minishell");
// }

// void	sig_handler(int signal)
// {
// 	printf("\n\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
// 	rl_on_new_line();
// 	rl_redisplay();
// }


// int g_errno = 0;

// void print_env(t_env *env)
// {
//     t_env *current = env;

//     while (current)
//     {
//         if (current->var)
//             printf("Variable: %s\n", current->var);
//         if (current->name)
//             printf("Name: %s\n", current->name);
//         if (current->value)
//             printf("Value: %s\n", current->value);
//         printf("\n");
//         current = current->next;
//     }
// }


int g_errno = 0;

int main(int ac, char **av, char **env)
{
    t_args cmd_line;

    (void)ac;
    (void)av;

    ft_bzero(&cmd_line, sizeof(t_args));
    environment(env, &cmd_line);

	cmd_line.fdin = dup(0);
	cmd_line.fdout = dup(1);
	if (cmd_line.fdin == -1 || cmd_line.fdout == -1)
		return (put_error(&cmd_line, DUPMSG, NULL), 130);
    while (1)
    {
        free_current_cmdline(&cmd_line);
        cmd_line.line = readline("\033[38;2;255;192;203m\033[1mminionshell^~^ \033[34m>$ \033[0m");
        if (cmd_line.line && *cmd_line.line)
            add_history(cmd_line.line);
        if (process_line(&cmd_line) != 0)
			continue ;
		if (execute_cmds(&cmd_line) != 0)
			continue ;
        t_cmd_tab *tab = cmd_line.table;

        while (tab)
        {
            if (tab->cmd)
            {
                // Affichage des commandes pour le débogage
                for (int i = 0; tab->cmd[i]; i++)
                    printf("cmd[%d]====%s\n", i, tab->cmd[i]);
            }
            printf("arg====%s\n", tab->arg);
            printf("append====%s\n", tab->append);
            while (tab->delimiter)
            {
                printf("limi====%s\n", tab->delimiter->content);
                tab->delimiter = tab->delimiter->next;
            }
            printf("infile====%s\n", tab->in);
            printf("outfile====%s\n", tab->out);
            printf("herecod====%d\n\n", tab->heredoc);
            // Exécution des commandes
            if (tab->cmd)
            {
                if (exec_builtin(&cmd_line, tab) == 0)
                {
                    single_cmd(tab); 
                }
            }
            tab = tab->next;
        }
        while (wait(0) != -1)
			continue ;
    }
    free_struct(&cmd_line);
    return 0;
}