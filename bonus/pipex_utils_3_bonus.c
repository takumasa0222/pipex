/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 04:35:59 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 18:15:39 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex_bonus.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

int	get_token_cnt(char const *str, char dlm)
{
	int	i;
	int	sp_cnt;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (ft_strlen(str) == 1)
		return (1);
	sp_cnt = 0;
	while (str[i])
	{
		while (str[i] == dlm && str[i])
			i++;
		if (!str[i])
			break ;
		while (str[i] != dlm && str[i])
			i++;
		sp_cnt++;
	}
	return (sp_cnt);
}

char	**ft_cmd_tokenizer(char *s, char c)
{
	int		i;
	int		j;
	char	**ret;
	int		token_cnt;

	token_cnt = get_token_cnt(s, c);
	ret = malloc((token_cnt + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (token_cnt + 1) && j < (int) ft_strlen(s))
	{
		while (s[j] == c)
			j++;
		get_next_word(s, &j, &ret[i], c);
		if (!ret[i])
			break ;
		i++;
		j++;
	}
	ret[i] = NULL;
	return (ret);
}

void	get_next_word(char *s, int *i, char **ret, char delim)
{
	char	*tmp;

	if (!s[*i])
		tmp = NULL;
	else if (s[*i] == SINGLE_QUOT)
	{
		(*i)++;
		tmp = get_single_quoeted_word(s, i);
	}
	else
		tmp = get_not_s_quoeted_word(s, i, delim);
	*ret = tmp;
}

char	*get_single_quoeted_word(char *s, int *i)
{
	int	initial_value;

	initial_value = *i;
	while (s[*i])
	{
		if (s[*i] == SINGLE_QUOT && *i)
			return (ft_substr(s, initial_value, *i - initial_value));
		(*i)++;
	}
	return (ft_substr(s, initial_value - 1, *i - initial_value + 1));
}

char	*get_not_s_quoeted_word(char *s, int *i, char c)
{
	int	initial_value;

	initial_value = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	return (ft_substr(s, initial_value, *i - initial_value));
}
