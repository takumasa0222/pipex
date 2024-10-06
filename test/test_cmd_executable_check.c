/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd_executable_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:42:47 by tamatsuu          #+#    #+#             */
/*   Updated: 2024/10/06 18:30:16 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../src/pipex.h"
#include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# define SINGLE_QUOT '\''

# define BASH_FILE_ERR_MSG "bash: "
# define CMD_NOT_FOUND_MSG "command not found\n"
# define PERMISSION_DENIED_MSG "Permission denied\n"
# define COLON ": "
# define PERMISSION_DENIED 1
# define CMD_NOT_FOUND 2

size_t	lencheck(size_t len, size_t str_len, unsigned int start, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_cmd_tokenizer(char *s, char c);
void	get_next_word(char *s, int *i, char **ret, char delim);
char	*get_single_quoeted_word(char *s, int *i);
char	*get_not_s_quoeted_word(char *s, int *i, char c);
size_t	ft_strlen(const char *s);
int	check_cmd_exec_w_path(char **cmd_path, char *cmd);

size_t	ft_strlen(const char *s)
{
	size_t			len;
	unsigned int	i;

	i = 0;
	len = 0;
	if (!s)
		return (i);
	while (s[i])
	{
		len++;
		i++;
	}
	return (len);
}

int	get_sep_cnt(char const *str, char dlm)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;
	unsigned int	j;
	size_t			str_len;

	if (!s || len > SIZE_MAX)
		return (NULL);
	str_len = ft_strlen(s);
	len = lencheck(len, str_len, start, (char *)s);
	ret = malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < start && i < (unsigned int)ft_strlen(s))
		i++;
	while (j < len && s[i] && j < len - 1)
	{
		ret[j] = s[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

size_t	lencheck(size_t len, size_t str_len, unsigned int start, char *s)
{
	if (str_len <= start || len == 0)
		return (1);
	if (str_len < len)
	{
		if (*s == '\0')
			return (1);
		if (str_len < len - start)
			return (str_len - start + 1);
		return (str_len + 1);
	}
	if (start + len > str_len)
		return (str_len - start + 1);
	return (len + 1);
}

char	**ft_cmd_tokenizer(char *s, char c)
{
	int		i;
	int		j;
	char	**ret;

	ret = malloc((get_sep_cnt(s, c) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < (get_sep_cnt(s, c) + 1) && j < ft_strlen(s))
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
	// else if (s[*i] == SINGLE_QUOT && is_not_escaped(s, *i))
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
		// if (s[*i] == SINGLE_QUOT && *i && is_not_escaped(s, *i))
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
	if (s[*i] == c)
		return (ft_substr(s, initial_value, *i - initial_value));
	else
		return (ft_substr(s, initial_value, *i- initial_value));
}



void	ft_printerr(char *err_msg, char *err_trg)
{
	if (!err_msg)
		return ;
	if (err_trg)
	{
		write(STDERR_FILENO, err_trg, ft_strlen(err_trg));
		write(STDERR_FILENO, COLON, ft_strlen(COLON));
	}
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	if (!s)
		return (NULL);
	ret = (char *)s;
	while (*ret)
	{
		if (*ret == (char)c)
			return (ret);
		ret++;
	}
	if ((char)c == '\0')
		return (ret);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*ret;
	size_t			i;
	size_t			j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len)
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

int	check_cmd_exec(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (0);
		return (2);
	}
	return (1);
}

void	cmd_executable_check(char **cmd, char **cmd_path)
{
	int		exec_status;

	exec_status = 0;
	if (!cmd)
		throw_err(NULL, BASH_GENERAL_ERR);
	if (!check_cmd_exec(cmd[0]) || !cmd_path)
		exec_status = check_cmd_exec(cmd[0]);
	else if (ft_strchr(cmd[0], '/'))
		exec_status = check_cmd_exec(cmd[0]);
	else if (!cmd[0])
		exec_status = 1;
	else
		exec_status = check_cmd_exec_w_path(cmd_path, cmd[0]);
	if (exec_status == 2)
	{
		ft_printerr("permission denied", cmd[0]);
		exit(126);
	}
	else if (exec_status == 1)
	{
		ft_printerr("command not found", cmd[0]);
		exit(127);
	}
}



int	check_cmd_exec_w_path(char **cmd_path, char *cmd)
{
	int		i;
	int		exec_status;
	char	*temp;
	char	*temp2;

	i = 0;
	exec_status = CMD_NOT_FOUND;
	while (cmd_path[i])
	{
		temp = ft_strjoin(cmd_path[i], "/");
		temp2 = ft_strjoin(temp, cmd);
		if (access(temp2, F_OK) == 0)
		{
			if (access(temp2, X_OK) == 0)
				return (free(temp), free(temp2), 0);
			exec_status = PERMISSION_DENIED;
		}
		i++;
		free(temp);
		free(temp2);
		temp = NULL;
		temp2 = NULL;
	}
	return (exec_status);
}



int main(int argc, char *argv[])
{ 
	char *arg = "cat";
	char **val;

	val = ft_cmd_tokenizer(arg, ' ');

	cmd_executable_check(val, NULL);
}
