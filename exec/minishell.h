/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:23:07 by kaafkhar          #+#    #+#             */
/*   Updated: 2024/09/21 00:39:05 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define BINARY_ERROR 127
# define FATAL_ERROR 130

# include <readline/readline.h>
# include <readline/history.h>
# include "libf/Libft/libft.h"
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
#include <libc.h>


extern int	g_errno;

typedef enum s_type
{
	redin = 2,
	redout = 3,
	heredoc = 4,
	append = 1,
	piipe = 5,
	string = 6,
	single_quote = 7,
	double_quote = 8,
	FLAG = 9,
}	t_type;

//command table
typedef struct s_cmd_tab
{
	char				**cmd;
	char				*arg;
	char				*in;
	char				*out;
	bool				heredoc;
	int					fd_heredoc;
	char				*append;
	t_list				*delimiter;
	struct s_cmd_tab	*next;
}	t_cmd_tab;

//tokens
typedef struct s_token
{
	void			*content;
	t_type			type;
	bool			space;
	struct s_token	*next;
}	t_token;

//main struct
typedef struct s_args
{
	t_list		*env;
	char		**path;
	char		*line;
	t_token		*tokens;
	t_cmd_tab	*table;
	int			cmd_num;
}	t_args;

// Environment list
typedef struct s_env
{
    char *var;
    char *value;
    struct s_env *next;
} t_env;

// builtins
void exec_builtin(t_args *args, t_cmd_tab *cmd);
int	ft_strcmp(const char *s1, const char *s2);
void exec_echo(t_args *args, t_cmd_tab *cmd);
int exec_cd(t_cmd_tab *cmd, t_list *env);
int ft_pwd(t_args *arg, char **cmd);
void exec_exit(t_args *args, t_cmd_tab *cmd);
int ft_export(t_args *arg, char **cmd);
int	own_strchr(char *str, char n);
int	is_num(char *str);
void exec_env(t_cmd_tab *cmd, t_list *env);
bool	get_flag(t_args *global, char *cmd);
char *get_path(t_list *env, const char *var_name);
void	environment(char **envp, t_args *cmd_line);


// freeing
void	free_array(char	**str);
void	free_tokens(t_token **lst);
void	del(void *content);
void	free_table(t_cmd_tab **table);
void	free_struct(t_args *cmd_line);


// Functions for environment management
int check_is_env(char *enve, t_list *env);
void delete_node(t_list **head, const char *key);


#endif