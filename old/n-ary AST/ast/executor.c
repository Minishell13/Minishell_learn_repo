/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:09 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/25 10:09:34 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_ast
{
	t_gram			type;	 // node kind
	struct s_ast	**children;
	
	union
	{
		char		**args;       // for AST_CMD: NULL‑terminated argv
		t_redir		redir;
		
	}	data;
}				t_ast;

// TODO: You need first to know the exact struct of AST tree
// TODO: The representation each node with his type and args
// TODO: How to parcoure throw this three and get nodes in the correct order
// TODO: Create functions for execution (per node type)
// TODO: Focus on execution flow, (memory, fds, error) management
// TODO: The leaks is fixed, now go and make behavioure like shell
// TODO: ...

int count_children(t_ast **ch);

// Return length of NULL-terminated pointer array
int count_children(t_ast **ch)
{
	int i = 0;
	if (!ch) return 0;
	while (ch[i]) i++;
	return i;
}

t_error	ft_executor(t_ast *root, t_ast *node, char **envp)
{
	if (!node) 
		return (SUCCESS);

	switch (node->type)
	{
	case GRAM_COMPLETE_COMMAND:
		// always exactly one child
		return ft_executor(root, node->children[0], envp);

	case GRAM_OPERATOR_AND:
	{
		return (ft_execute_and_or(root, node, envp));
	}

	case GRAM_OPERATOR_OR:
	{
		return (ft_execute_and_or(root, node, envp));
	}

	case GRAM_PIPELINE:
	{
		return (ft_execute_pipe(root, node, envp));
	}

	case GRAM_IO_REDIRECT:
	{
		expand_redir(node);
		return (ft_execute_redirection(root, node, envp));
	}

	case GRAM_SIMPLE_COMMAND:
	{
		// TODO: If buitins == export expand just $VAR not * Wildcard
		if (is_builtins(node))
			return (exec_builtins(root, node));
		else
		{
			expand_cmd_node(node, process_mode_1);
			return (ft_execute_simple_cmd(root, node, envp));
		}
	}

	case GRAM_SUBSHELL:
	{
	   return (ft_execute_subshell(root, node, envp));
	}

	default:
		return (SUCCESS);
	}
}
