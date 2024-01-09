#include "../../includes/mini_shell.h"

void	ft_remove_char_in_str(char *str, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != c)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

int	ft_find_char_index_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !c)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_count_char(char *str, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str == 0)
		return (0);
	while (str[++i])
	{
		if (str[i] == c)
			ret ++;
	}
	return (ret);
}

int	ft_remove_quotes(char *str, int single_quote, int double_quotes,
	int index_double_quotes)
{
	int	index_single_quote;

	index_single_quote = ft_find_char_index_str(str, '\'');
	if (single_quote > 0 && double_quotes == 0)
	{
		ft_remove_char_in_str(str, '\'');
		return (1);
	}
	if (double_quotes > 0 && single_quote == 0)
	{
		ft_remove_char_in_str(str, '\"');
		return (1);
	}
	if (index_double_quotes > index_single_quote)
	{
		ft_remove_char_in_str(str, '\'');
		return (0);
	}
	if (index_single_quote > index_double_quotes)
	{
		ft_remove_char_in_str(str, '\"');
		return (0);
	}
	return (1);
}

int	ft_cd_with_quotes(char *str)
{
	int	single_quote;
	int	double_quotes;
	int	total_quotes;
	int	index_double_quotes;
	int	res;

	single_quote = ft_count_char(str, '\'');
	double_quotes = ft_count_char(str, '\"');
	total_quotes = single_quote + double_quotes;
	index_double_quotes = ft_find_char_index_str(str, '\"');
	if (total_quotes > 0)
	{
		res = ft_remove_quotes(str, single_quote, double_quotes,
				index_double_quotes);
		if (res == 1)
			return (1);
		else
			return (0);
	}
	return (1);
}