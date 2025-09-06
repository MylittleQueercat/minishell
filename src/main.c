/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:19:45 by hguo              #+#    #+#             */
/*   Updated: 2025/09/05 16:03:30 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

static void	init_minishell(t_minishell *sh, char **env)
{
	ft_bzero(sh, sizeof(*sh));
	sh->envlst = env;
	init_envlst(sh);
	sh->fd_stdin = dup(STDIN_FILENO);
	sh->fd_stdout = dup (STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &sh->original_term);
}

static void	go_execution(t_minishell *sh)
{
	signal(SIGQUIT, sig_quit_handler);
	init_tree(sh->tree);
	if (g_sigstate.heredoc_sigint)
	{
		clear_ast(&sh->tree);
		g_sigstate.heredoc_sigint = false;
		return ;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
	sh->exit_s = executor(sh);
	clear_ast(&sh->tree);
}

static void	run_iteration(t_minishell *sh)
{
	init_signals(sh);
	sh->line = readline(PROMPT);
	if (!sh->line)
		eof_exit(sh);
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenize(sh);
	if (!sh->tokens)
		return (free(sh->line), (void)(sh->line = NULL));
	sh->tree = parse(sh);
	if (sh->parse_err.type)
	{
		handle_parse_err(sh);
		clear_ast(&sh->tree);
		clear_token_list(&sh->tokens);
		return (free(sh->line), (void)(sh->line = NULL);
		(void)(sh->parse_err.type = 0));
	}
	if (!expand_ast(sh, sh->tree->raw_args))
	{
		clear_ast(&sh->tree);
		clear_token_list(&sh->tokens);
		free(sh->line);
		sh->line = NULL;
		return ;
	}
	go_execution(sh);
	clear_token_list(&sh->tokens);
	free(sh->line);
	sh->line = NULL;
	sh->parse_err.type = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell	sh;

	(void)ac;
	(void)av;
	init_minishell(&sh, env);
	while (1)
		run_iteration(&sh);
	go_trash(NULL, true);
	clean_message(&sh);
	return (sh.exit_s);
}
*/


#include "minishell.h"

/*
static void	sigint_handler(int signo)
{
	(void)signo;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_redisplay();
}
	*/

# include <signal.h>

int main(int argc, char **argv, char **envp)
{
    t_minishell sh;

    (void)argc;
    (void)argv;
	(void)envp;
	ft_bzero(&sh, sizeof(t_minishell));
	rl_catch_signals = 0;
	init_signals(&sh);

  //  init_envlst(&sh, envp);

    while (1)
    {
        sh.line = readline("expander_test$ ");
        if (!sh.line) // Ctrl-D
            break;
        if (sh.line[0])
            add_history(sh.line);

        // tokenizer
        sh.tokens = tokenizer(&sh);
        if (!sh.tokens)
            continue;

        // parser
        sh.tree = parse(&sh);
        if (sh.parse_err.type)
        {
            handle_parse_err(&sh);
            clear_token_list(&sh.tokens);
            clear_ast(&sh.tree);
            free(sh.line);
            sh.line = NULL;
            continue;
        }
		free(sh.line);
			sh.line = NULL;

        // expander
		sh.line = readline("expander_tests> ");
		if (!sh.tree)
		{
			clear_token_list(&sh.tokens);
			clear_ast(&sh.tree);
			break;
		}
        if (sh.tree)
        {
            expander(&sh, sh.tree->raw_args);
            if (sh.tree->type == N_CMD && sh.tree->exec_args)
            {
                for (int i = 0; sh.tree->exec_args[i]; i++)
                    printf("arg[%d] = %s\n", i, sh.tree->exec_args[i]);
            }
        }
        clear_token_list(&sh.tokens);
        clear_ast(&sh.tree);
        free(sh.line);
        sh.line = NULL;
    }
	
    clean_message(&sh);
    return 0;
}
