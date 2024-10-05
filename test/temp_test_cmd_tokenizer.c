#include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# define SINGLE_QUOT '\''


size_t	lencheck(size_t len, size_t str_len, unsigned int start, char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_cmd_tokenizer(char *s, char c);
void	get_next_word(char *s, int *i, char **ret, char delim);
char	*get_single_quoeted_word(char *s, int *i);
char	*get_not_s_quoeted_word(char *s, int *i, char c);
size_t	ft_strlen(const char *s);

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


void	test_cmd(char *s)
{
	char	**result;

	result = NULL;
	result = ft_cmd_tokenizer(s, ' ');
    for (int i = 0; result && result[i]; i++) {
        printf("result is %s\n", result[i]);
    }
	printf("test done \n\n");
	for (int j = 0; result[j]; j++)
	{
		free(result[j]);
	}
	free(result);
}

int main(int argc, char *argv[])
{
	char	**result;
	char	*test = "awk\0";
	char	*test1 = "awk '{print $1}'";
	char	*test2 = "   awk '{print $1}'   ";
	char	*test3 = "   awk '{print $1}'  abc\0";
	char	*test4 = "   awk '{print $1}'  'asd'\0";
	char	*test5 = "   awk '{print $1}'  'asert\0";
	char	*test6 = "cat '  asdf  ' ' aasdf  ' ' as'";


	test_cmd(test);
	test_cmd(test1);
	test_cmd(test2);
	test_cmd(test3);
	test_cmd(test4);
	test_cmd(test5);
	test_cmd(test6);
	if (argc > 1)
		test_cmd(argv[1]);

}
