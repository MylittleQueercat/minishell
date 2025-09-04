/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:19:45 by hguo              #+#    #+#             */
/*   Updated: 2025/09/04 18:52:41 by hguo             ###   ########.fr       */
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


/*
#include "minishell.h"

// 简单清理
int main(int argc, char **argv, char **envp)
{
    t_minishell sh;

    (void)argc;
    (void)argv;
	(void)envp;
    ft_bzero(&sh, sizeof(t_minishell));

    // 初始化环境链表（你需要自己写的函数，比如 init_envlst）
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

        // expander
        // 遍历 AST，对 command 节点做 expand
        // （你需要实现 expand_node/expand_cmd 等函数）
		sh.line = readline("expander_tests> ");
		if (!sh.tree)
			break;
        if (sh.tree)
        {
            expander(&sh, sh.tree->raw_args);
            // 打印测试结果：例如显示 command 的 exec_args
            if (sh.tree->type == N_CMD && sh.tree->exec_args)
            {
                for (int i = 0; sh.tree->exec_args[i]; i++)
                    printf("arg[%d] = %s\n", i, sh.tree->exec_args[i]);
            }
        }

        // 清理，准备下一轮
        clear_token_list(&sh.tokens);
        clear_ast(&sh.tree);
        free(sh.line);
        sh.line = NULL;
    }
    clean_message(&sh);
    return 0;
}
*/