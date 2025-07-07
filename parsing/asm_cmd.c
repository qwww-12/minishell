/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:31 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/06 17:19:38 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*assemble_command(char *input, t_env *env)
{
	t_cmd	*cmd;
	t_token	*tokens;

	tokens = NULL;
	if (!quotes_is_valid(input))
	{
		exit_status(258);
		return (first_free(tokens, input), printf(ERR_QUOTES), NULL);
	}
	env_space(&input, env);
	tokens = segment_input(input);
	if (!tokens)
		return (p1char(&input), NULL);
	if (!all_scrap(tokens))
		return (first_free(tokens, input), exit_status(258), NULL);
	refactor_tokens(&tokens, env);
	cmd = create_list_cmd(tokens);
	if (!hydrate_cmd(&cmd, tokens))
		return (first_free(tokens, input), NULL);
	first_free(tokens, input);
	return (cmd);
}
