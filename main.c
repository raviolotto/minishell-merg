/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:59:42 by jcardina          #+#    #+#             */
/*   Updated: 2024/02/01 15:47:37 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/mini_shell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char) c)
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;

	len_src = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != 0 && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (len_src);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*news;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	news = malloc (sizeof(char) * (end - start + 2));
	if (!news)
		return (NULL);
	ft_strlcpy(news, s1 + start, (end - start + 2));
	return (news);
}

char *cleaner(char *str)
{
	char *new;
	if(str[0] == '\'')
		new = ft_strtrim(str, "\'");
	else
		new = ft_strtrim(str, "\"");
}

int main(int ac, char **av)
{
	char *str;
	char *tmp;
	if(ac == 3 || ac == 5)
	{
		str = av[1] + 2;
		str = ft_strtrim(str, " ");
		tmp = cleaner(str);
		free(str);
		//free(command)
		//command = tmp;
	}
	else
	{
		str = av[1] + 1;
		str = ft_strtrim(str, " ");
		tmp = cleaner(str);
		//free(command)
		//command = tmp;
	}
}
