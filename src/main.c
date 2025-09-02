/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:19:45 by hguo              #+#    #+#             */
/*   Updated: 2025/09/02 17:33:28 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// tests/main_expander_test.c
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

/* ---------- 打印辅助：展示展开后的结果 ---------- */
static void print_strv(const char *label, char **v) {
    printf("  %s:", label);
    if (!v) { printf(" (null)\n"); return; }
    printf("\n");
    for (int i = 0; v[i]; i++) printf("    [%d] \"%s\"\n", i, v[i]);
}

static void print_io(const t_io_node *io) {
    for (; io; io = io->next) {
        const char *op = io->type==IO_IN?"<":io->type==IO_OUT?">":
                         io->type==IO_HEREDOC?"<<":">>";
        printf("  IO  : %s raw=\"%s\" heredoc=%d\n",
               op, io->raw_value?io->raw_value:"", io->heredoc);
        print_strv("exec_value", io->exec_value);
    }
}

static void print_ast_after_expand(const t_node *n, int d) {
    if (!n) return;
    for (int i=0;i<d;i++) printf("  ");
    if (n->type==N_CMD) {
        printf("[CMD] raw_args=\"%s\"\n", n->raw_args?n->raw_args:"");
        print_strv("exec_args", n->exec_args);
        print_io(n->io_list);
    } else if (n->type==N_PIPE) { puts("[PIPE]"); }
      else if (n->type==N_AND) { puts("[AND]"); }
      else if (n->type==N_OR) { puts("[OR]"); }
    if (n->left)  print_ast_after_expand(n->left, d+1);
    if (n->right) print_ast_after_expand(n->right, d+1);
}

/* ---------- 一轮：读→词法→语法→展开→打印→清理 ---------- */
static void one_round(t_minishell *sh) {
    sh->line = readline("expander$ ");
    if (!sh->line) { puts("exit"); clean_message(sh); exit(sh->exit_s); }
    if (sh->line[0]) add_history(sh->line);

    sh->tokens = tokenizer(sh);                           // TODO: 若函数名不同请替换
    if (!sh->tokens) { free(sh->line); sh->line=NULL; return; }

    sh->tree = parse(sh);                                 // TODO: 若函数名不同请替换
    if (sh->parse_err.type) {
        handle_parse_err(sh);
        clear_ast(&sh->tree); clear_token_list(&sh->tokens);
        free(sh->line); sh->line=NULL; sh->parse_err.type=0; return;
    }

    /* ====== 关键：调用你的 expander ====== */
    /* 任选一种（按你项目实际来），把没用的行注释掉即可： */
    // int ok = ft_expand(sh, sh->tree);                  // 方案 A：整棵树
    // int ok = expand_tree(sh, sh->tree);                // 方案 B：整棵树（另名）
    int ok = 1; /* 如果你只有逐节点接口，可在递归里调用 expand_cmd(sh,node) 等 */

    if (!ok) {
        fprintf(stderr, "expander: memory error?\n");
        clear_ast(&sh->tree); clear_token_list(&sh->tokens);
        free(sh->line); sh->line=NULL; return;
    }

    /* 展开后打印观察 */
    print_ast_after_expand(sh->tree, 0);

    /* 清理一轮 */
    clear_ast(&sh->tree);
    clear_token_list(&sh->tokens);
    free(sh->line); sh->line = NULL;
}

/* ---------- 入口：初始化最小环境，然后循环 ---------- */
int main(int ac, char **av, char **envp) {
    (void)ac; (void)av; (void)envp;
    t_minishell sh; ft_bzero(&sh, sizeof(sh));
//    sh.envlst = envp;            // 让 expander 能查 $VAR
//    init_envlst(&sh, envp);           // TODO: 若需要环境链表，传 &sh 或 sh，按你的原型
    while (1) one_round(&sh);
    return 0;
}


// #include "minishell.h"
/*
static void init_minishell(t_minishell *sh, char **env)
{
	ft_bzero(sh, sizeof(*sh));
	sh->envlst = env;
	init_envlst(sh);
	sh->fd_stdin = dup(STDIN_FILENO);
	sh->fd_stdout = dup (STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &sh->original_term);
}

static void go_execution(t_minishell *sh)
{
	signal(SIGQUIT, sig_quit_handler);
	init_tree(sh->ast);
	if (g_sigstate.heredoc_sigint)
	{
		clear_ast(&sh->ast);
		g_sigstate.heredoc_sigint = false;
		return ;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &sh->original_term);
	sh->exit_s = executor(sh);
	clear_ast(&sh->ast);
}

static void run_iteration(t_minishell *sh)
{
	init_signals(sh);
	sh->line = readline(PROMPT);
	if (!sh->line)
		eof_exit(t_minishell *sh);
	if (sh->line[0])
		add_history(sh->line);
	sh->tokens = tokenize(sh);
	if (!sh->tokens)
		return (free(sh->line), (void)(sh->line = NULL));
	sh->ast = parse(sh);
	if (sh->parse_err.type)
	{
		handle_parse_err(sh);
		clear_ast(&sh->ast);
		clear_token_list(&sh->tokens);
		return (free(sh->line), (void)(sh->line = NULL), 
		(void)(sh->parse_err.type = 0));
	}
	go_execution(sh);
	clear_token_list(&sh->tokens);
	free(sh->line);
	sh->line = NULL;
	sh->parse_err.type = 0;
}

int	main(int ac, char **av, char **env)
{
	t_minishell sh;

	(void)ac;
	(void)av;
	init_minishell(&sh, env);
	while (1);
		run_iteration(&sh);
	go_trash(NULL, true);
	clean_message(&sh);
	return (sh.exit_s);
}
*/
/*
// test of token.c
int main(void) 
{
    t_minishell sh = {0};

    while (1) 
    {
        sh.line = readline("minishell$ ");
        if (!sh.line) 
            break;
        if (*sh.line) 
            add_history(sh.line);
        sh.tokens = tokenizer(&sh);
        clear_token_list(&sh.tokens);
        free(sh.line);
        sh.line = NULL;              
    }
    clear_token_list(&sh.tokens);
    clear_history();                       
    return 0;
}
*/


/*
// tests/parse.c
#include "minishell.h"
#include <stdio.h>

static void print_io_list(const t_io_node *io)
{
    while (io)
    {
        const char *op = "??";
        if (io->type == IO_IN)      op = "<";
        else if (io->type == IO_OUT)     op = ">";
        else if (io->type == IO_HEREDOC) op = "<<";
        else if (io->type == IO_ADD_END)  op = ">>";

        fprintf(stdout, "    IO  : %-2s  raw='%s'\n", op, io->raw_value ? io->raw_value : "");
        io = io->next;
    }
}

static void print_ast(const t_node *n, int depth)
{
    if (!n) return;

    for (int i = 0; i < depth; i++) fputs("  ", stdout);

    switch (n->type) {
    case N_PIPE: fputs("[PIPE]\n", stdout); break;
    case N_AND:  fputs("[AND]\n",  stdout); break;
    case N_OR:   fputs("[OR]\n",   stdout); break;
    case N_CMD:
        fprintf(stdout, "[CMD] raw_args=\"%s\"\n", n->raw_args ? n->raw_args : "");
        if (n->io_list) print_io_list(n->io_list);
        break;
    default:
        fputs("[UNKNOWN]\n", stdout); break;
    }

    if (n->left)  print_ast(n->left,  depth + 1);
    if (n->right) print_ast(n->right, depth + 1);
}

int main(void)
{
    t_minishell sh;
    ft_bzero(&sh, sizeof(sh));  // 或 sh = (t_minishell){0};

    while (1) {
        sh.line = readline("minishell$ ");
        if (!sh.line) break;                // Ctrl-D 退出
        if (*sh.line) add_history(sh.line);

        sh.tokens = tokenizer(&sh);
        if (sh.parse_err.type) {
            fprintf(stderr, "tokenize error: %d\n", sh.parse_err.type);
            clear_token_list(&sh.tokens);
            free(sh.line);
            sh.line = NULL;
            sh.parse_err.type = 0;
            continue;
        }

        t_token *it = sh.tokens;
        t_node  *tree = parse_cmd(&sh, &it, 0);   
        if (sh.parse_err.type) {
            fprintf(stderr, "parse error: %d\n", sh.parse_err.type);
        } else if (it) {
            fprintf(stderr, "parse error: trailing tokens\n");
        } else {
            print_ast(tree, 0);
        }

        clear_ast(&tree);
        clear_token_list(&sh.tokens);
        free(sh.line);
        sh.line = NULL;
        sh.parse_err.type = 0;
    }
    clear_token_list(&sh.tokens);
    free(sh.line);
    return 0;
}
*/

