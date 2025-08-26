/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 19:19:45 by hguo              #+#    #+#             */
/*   Updated: 2025/08/26 20:37:09 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
