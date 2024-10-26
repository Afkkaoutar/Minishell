/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaafkhar <kaafkhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:41:54 by ychagri           #+#    #+#             */
/*   Updated: 2024/10/26 02:23:28 by kaafkhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_opn(t_cmd_tab *cmd)
{
	int		fdin;
	t_list	*tmp;
	char	*infile;

	if (cmd->in != NULL)
	{
		tmp = cmd->in;
		while (tmp)
		{
			if (check_files(cmd->data, tmp->content, INPUT))
				return (1);
			if (tmp->next == NULL)
				infile = tmp->content;
			tmp = tmp->next;
		}
		if (ft_strncmp(tmp->content, "/dev/stdin", ft_strlen(infile) + 1) == 0)
			fdin = STDIN_FILENO;
		else
		{
			fdin = open(infile, O_RDONLY, 0644);
			if (fdin == -1)
				return (put_error(cmd->data, OPENMSG, NULL), 1);
		}
		if (cmd->heredoc == false)
		{
			if (dup2(fdin, STDIN_FILENO == -1))
				return (close(fdin), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdin);
	}
	if (cmd->heredoc == true)
	{
		if (dup2(cmd->fd_heredoc, STDIN_FILENO == -1))
			return (close(cmd->fd_heredoc),
				put_error(cmd->data, DUP2SG, NULL), 1);
		close(cmd->fd_heredoc);
	}
	return (0);
}

int	append_red(t_cmd_tab *cmd)
{
	int		apnd;
	t_list	*tmp;
	char	*str;

	tmp = cmd->append;
	while (tmp)
	{
		if (check_files(cmd->data, tmp->content, OUTPUT))
			return (1);
		str = tmp->content;
		if (*str == 0)
			return (put_error(cmd->data, INTROUVABLE_FILE, NULL), 1);
		apnd = open(tmp->content, O_CREAT | O_APPEND | O_RDWR, 0644);
		if (apnd == -1)
			return (put_error(cmd->data, OPENMSG, NULL), 1);
		if (tmp->next)
			close(apnd);
		tmp = tmp->next;
	}
	if (cmd->red_out == APND)
	{
		if (dup2(apnd, STDOUT_FILENO) == -1)
			return (close(apnd), put_error(cmd->data, DUP2SG, NULL), 1);
	}
	close(apnd);
	return (0);
}

int	outfile_opn(t_cmd_tab *cmd)
{
	int		fdout;
	t_list	*tmp;
	char	*outfile;

	if (cmd->out != NULL)
	{
		tmp = cmd->out;
		while (tmp)
		{
			if (check_files (cmd->data,tmp->content, OUTPUT))
				return (1);
			if (ft_strncmp(tmp->content, "/dev/stdout",
					ft_strlen(tmp->content) + 1) == 0)
				fdout = STDOUT_FILENO;
			else
			{
				outfile = tmp->content;
				if (*outfile == 0)
					return (put_error(cmd->data, INTROUVABLE_FILE, NULL), 1);
				fdout = open(tmp->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
				if (fdout == -1)
					return (put_error(cmd->data, OPENMSG, NULL), 1);
				if (tmp->next != NULL)
					close (fdout);
			}
			tmp = tmp->next;
		}
		if (cmd->red_out == REDOUT)
		{
			if (dup2(fdout, STDOUT_FILENO) == -1)
				return (close(fdout), put_error(cmd->data, DUP2SG, NULL), 1);
		}
		close(fdout);
	}
	if (cmd->append != NULL)
		return (append_red(cmd));
	return (0);
}
