/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarhoun <mbarhoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 18:02:14 by mbarhoun          #+#    #+#             */
/*   Updated: 2025/07/20 18:21:46 by mbarhoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	just_slash(char *dir)
{
	int		r;

	r = 0;
	while (dir[r])
	{
		if (dir[r] != '/')
			return (0);
		r++;
	}
	return (1);
}

bool	has_slash(char *dir)
{
	int		r;

	r = 0;
	while (dir[r])
	{
		if (dir[r] == '/')
			return (1);
		r++;
	}
	return (0);
}

void	handle_slash(char **anv, char *dir, char *path)
{
	if (just_slash(dir))
	{
		is_directory(dir);
		p2char(&anv);
		p1char(&path);
		exit(126);
	}
	if (has_slash(dir) && access(dir, F_OK) == -1)
	{
		is_not_directory(dir);
		p2char(&anv);
		p1char(&path);
		exit(127);
	}
}
