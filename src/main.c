/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:19:45 by hguo              #+#    #+#             */
/*   Updated: 2025/08/27 20:53:43 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

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

