/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:49:24 by abnsila           #+#    #+#             */
/*   Updated: 2025/05/24 13:20:00 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

// Libft
# include "../Libft/includes/libft.h"

// Log
# include <stdio.h>

// Directory
# include <dirent.h> 

// Readline
# include <readline/readline.h>
# include <readline/history.h>

// Time
# include <sys/wait.h>

// Utils function
# include <stdlib.h>
# include <string.h>

// Error
# include <errno.h>

typedef struct	s_minishell
{
	char	*shell;
	char	**env;
	char	**my_env;
	int		exit_code;
}				t_minishell;

typedef enum e_error
{
	SUCCESS,
	ERROR,
	MALLOC_ERROR,
	FORK_ERROR,
	PIPE_ERROR,
	DUP_ERROR,
	DUP2_ERROR,
	REDIR_ERROR,
	EXECVE_ERROR,
	CMD_NOT_FOUND,
	FILE_NOT_EXIST,
}			t_error;

typedef enum e_exit_code
{
	NO_FILE_OR_DIR = 127,
	PERMISSION_DENIED = 126,

}			t_exit_code;

typedef enum s_token_type 
{
	TOKEN_WORD,
	TOKEN_PIPE,        // |
	TOKEN_REDIR_IN,    // <
	TOKEN_REDIR_OUT,   // >
	TOKEN_REDIR_APPEND,// >>
	TOKEN_HEREDOC,     // <<
	TOKEN_AND,         // &&
	TOKEN_OR,          // ||
	TOKEN_OPARENTHES,  // (
	TOKEN_CPARENTHES,  // )
	TOKEN_EMPTY,
} t_token_type;

typedef enum s_gram 
{
	UNKNOWN,
	GRAM_COMPLETE_COMMAND,
	GRAM_COMMAND_LIST,
	GRAM_COMPOUND_COMMAND,
	GRAM_PIPELINE,
	GRAM_COMMAND,
	GRAM_SUBSHELL,
	GRAM_SIMPLE_COMMAND,
	GRAM_REDIRECT_LIST,
	GRAM_IO_REDIRECT,
	GRAM_WORD,
	GRAM_OPERATOR_AND,     // &&
	GRAM_OPERATOR_OR,      // ||
	GRAM_OPERATOR_PIPE,    // |
	GRAM_REDIR_IN,         // <
	GRAM_REDIR_OUT,        // >
	GRAM_REDIR_APPEND,     // >>
	GRAM_HEREDOC,          // <<
	GRAM_FILENAME,         // filename after redirection
	GRAM_LINEBREAK
} 			t_gram;

typedef struct	s_token
{
	char			*value;   // allocated string slice
	t_token_type	type;   // token kind
	struct s_token	*next;   // next in list
	struct s_token	*prev;   // previous in list
}				t_token;

typedef struct	s_redir
{
	t_gram	type;
	char	*file;
	char	*limiter;
	t_bool	expanded;
}				t_redir;

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

typedef enum	s_qmode
{
	DEFAULT,
	LITERAL,
	EXPAND
}				t_qmode;

typedef enum	s_quote
{
	NONE,
	SINGLE_Q,
	DOUBLE_Q
}				t_quote;

// For $VAR expansion
typedef struct	s_block
{
	char			*text;       // "$USER", '"', etc.
	t_qmode	mode;
	t_quote			quote;
}				t_block;

#endif
