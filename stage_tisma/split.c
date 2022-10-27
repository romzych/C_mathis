#include "header.h"

char	**ft_split(char *str)
{
	char	**tab;

	if (!str)
	{
		if (!(tab = malloc(sizeof(char *) * 1)))
			return (0);
		tab[0] = 0;
		return (tab);
	}
	if (!(tab = malloc(sizeof(char *) * (ft_count_word(str, "\n") + 1))))
		return (0);
	ft_fill_tab(tab, str, "\n", ft_count_word(str, "\n"));
	return (tab);
}

int		ft_strlen_count(char *str, char *charset, int i)
{
	int y;

	y = 0;
	while (ft_cmp(str[i], charset) == 0 && str[i])
	{
		i++;
		y++;
	}
	return (y + 1);
}

void	ft_fill_tab(char **tab, char *str, char *charset, int wordnbr)
{
	int i;
	int y;
	int x;

	i = 0;
	y = 0;
	while (y < wordnbr)
	{
		x = 0;
		while (ft_cmp(str[i], charset) == 1 && str[i])
			i++;
		tab[y] = malloc(sizeof(char) * ft_strlen_count(str, charset, i));
		if (!tab)
			return ;
		while (ft_cmp(str[i], charset) == 0 && str[i])
		{
            write(1, &str[i], 1);
			tab[y][x] = str[i];
			i++;
			x++;
		}
		tab[y][x] = 0;
		y++;
	}
	tab[y] = 0;
}

int		ft_count_word(char *str, char *charset)
{
	int i;
	int wc;

	wc = 0;
	i = 0;
	while (str[i])
	{
		while (ft_cmp(str[i], charset) == 1 && str[i])
			i++;
		if (!str[i])
			return (wc);
		wc++;
		while (ft_cmp(str[i], charset) == 0 && str[i])
			i++;
	}
	return (wc);
}

int		ft_cmp(char str, char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if (str == charset[i])
			return (1);
		i++;
	}
	return (0);
}
