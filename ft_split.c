/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pdong <pdong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 18:52:32 by pdong         #+#    #+#                 */
/*   Updated: 2023/01/11 17:59:18 by pdong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	wordlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	if (s[i] == 34 || s[i] == 39)
	{
		i++;
		while (s[i] && s[i] != 34 && s[i] != 39)
		{
			i++;
			len++;
		}
		return (len);
	}
	while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
	{
		i++;
		len++;
	}
	return (len);
}

int	mem_str(char **ans, int k, int len)
{
	ans[k] = malloc(sizeof(char) * (len + 1));
	if (!ans[k])
	{
		while (k >= 0)
		{
			free(ans[k]);
			k--;
		}
		return (0);
	}
	return (1);
}

char	**arrmake(char const *s, char c, char **ans, int wcount)
{
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	k = 0;
	while (s[i] == c)
		i++;
	while (s[i] && k < wcount)
	{
		j = 0;
		len = wordlen(s, c, i);
		if (mem_str(ans, k, len) == 0)
			return (NULL);
		while (j < len)
			ans[k][j++] = s[i++];
		ans[k][j] = 0;
		k++;
		while (s[i] == c || s[i] == 34 || s[i] == 39)
			i++;
	}
	ans[k] = NULL;
	return (ans);
}

int	wcounter(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == 34 || s[i] == 39)
		{
			wcount++;
			i++;
			while (s[i] && s[i] != 34 && s[i] != 39)
				i++;
			i++;
		}
		while (s[i] == c)
			i++;
		if (s[i])
			wcount++;
		while (s[i] && s[i] != c && s[i] != 34 && s[i] != 39)
			i++;
	}
	return (wcount);
}

int	qcounter(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	char	**ans;

	if (!s || !*s)
	{
		ans = malloc(sizeof(char *) * 1);
		if (!ans)
			return (NULL);
		ans[0] = NULL;
		return (ans);
	}
	wcount = wcounter(s, c);
	if (qcounter(s) % 2 != 0)
		return (NULL);
	ans = malloc(sizeof(char *) * (wcount + 1));
	if (!ans)
		return (NULL);
	ans = arrmake(s, c, ans, wcount);
	return (ans);
}

int main(int ac, char **av)
{
	int i = 0;
	char **a = ft_split(av[1], 0);
	while (a[i])
	{
		printf("%s\n", a[i]);
		free(a[i]);
		i++;
	}
	free(a);
	system("leaks -q a.out");
}

/*usage:
gcc ft_split.c && ./a.out "grep \"abc def\" aaa"
input to function: grep "abc def" aaa
wcount: 3
grep 
abc def
 aaa
leaks Report Version: 4.0
Process 7322: 163 nodes malloced for 18 KB
Process 7322: 0 leaks for 0 total leaked bytes.
*/