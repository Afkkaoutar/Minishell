/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 20:14:06 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/21 00:42:26 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_seperator(char c)
{
	return (c == '|' || c == '<' || c == '>' );
}

void	environment(char **envp, t_args *cmd_line)
{
	t_list	*node;
	t_list	*prev;
	int		i;
	char	*str;
	char	**pathh;

	str = getenv("PATH");
	pathh = ft_split(str, ':');
	prev = NULL;
	cmd_line->path = pathh;
	i = 0;
	while (envp[i])
	{
		node = ft_lstnew(envp[i]);
		node->previous = prev;
		prev = node;
		ft_lstadd_back(&cmd_line->env, node);
		i++;
	}
}

void	s()
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
    atexit(s);
    (void)argc;
    (void)argv;
    t_args args;
    t_cmd_tab cmd;
    char *input_line;
    
    args.env = NULL;
    environment(envp, &args);

    while (1)
    {
        // dekhla
        input_line = readline("minishell:)> ");
        if (!input_line)
            break;
        
        // ajouti cmd lreadline
        add_history(input_line);
        
        // Initialise lcmd bach tester
        cmd.cmd = ft_split(input_line, ' ');
        cmd.arg = cmd.cmd[1]; // arg optionnel
        
        // Exécution
        if (cmd.cmd[0])
            exec_builtin(&args, &cmd);
        free_array(cmd.cmd);
        free(input_line);
    }
    free_struct(&args);
    return 0;
}
