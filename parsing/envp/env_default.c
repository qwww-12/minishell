/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:45:51 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/18 12:22:20 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*default_env(void)
{
	t_env	*env;

	env = new_env(ft_strdup("PWD"), getcwd(NULL, 0), 1);
	env->next = new_env(ft_strdup("SHLVL"), ft_strdup("0"), 1);
	env->next->next = new_env(ft_strdup("_"), ft_strdup("/usr/bin/env"), 1);
	env->next->next->next = new_env(ft_strdup("OLDPWD"), ft_strdup(""), 0);
	return (env);
}
