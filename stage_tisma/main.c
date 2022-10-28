#include "header.h"
#include <stdio.h>

char *file_to_str(char *file_path, int file_size)
{
    char	*str;
    int		fd;

	fd = open(file_path, O_RDONLY);
    if (!(str = malloc(sizeof(char) * file_size + 1)))
        return (0);
    read(fd, str, file_size);
    str[file_size + 1] = 0;
    return (str);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}


int ft_size_file(char *file_path)
{
    char buf[BUF_SIZE + 1];
    int bytes;
    unsigned long count;
    int fd;

    count = 0;
    fd = open(file_path, O_RDONLY);
    while((bytes = read(fd, buf, BUF_SIZE)))
    {
        if (bytes == 0)
        {
            close(fd);
            return (0);
        }
        count += bytes;
    }
    close(fd);
    return (count);
}

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

double ft_fill_tps(char *str)
{
    int i;
    double value;
    char *temp;

    i = 0;
    if (!(temp = malloc(sizeof(char) * 4)))
        return (0);
    while (i < 4)
    {
        temp[i] = str[i];
        i++;
    }
    if (!(value = malloc(sizeof(double) * atof(temp))))
        return (0);
    value = atof(temp);
    return (value);
}

double ft_fill_speed(char *str)
{
    int i;
    int y;
    double value;
    char *temp;

    i = 8;
    y = 0;
    if (!(temp = malloc(sizeof(char) * 4)))
        return (0);
    while (i < 13)
    {
        temp[y] = str[i];
        i++;
        y++;
    }
    if (!(value = malloc(sizeof(double) * atof(temp))))
        return (0);
    value = atof(temp);
    return (value);
}

double ft_fill_fractionmassique(char *str)
{
    int i;
    int y;
    double value;
    char *temp;

    i = 15;
    y = 0;
    if (!(temp = malloc(sizeof(char) * 4)))
        return (0);
    while (i < 20)
    {
        temp[y] = str[i];
        i++;
        y++;
    }
    if (!(value = malloc(sizeof(double) * atof(temp))))
        return (0);
    value = atof(temp);
    return (value);
}

void ft_parse(char **tab, t_line *struct_tab)
{
    int i;
    
    i = 1;
    while (tab[i])
    {
        struct_tab[i].tps = ft_fill_tps(tab[i]);
        struct_tab[i].speed = ft_fill_speed(tab[i]);
        struct_tab[i].fractionmassique = ft_fill_fractionmassique(tab[i]);
        i++;
    }
}


int main(void)
{
    char *file_path;
    char *str_temp;
	char **tab;
    t_line  *struct_tab;

    file_path = "Questions_fortran_C_dataentree.txt";
    str_temp = file_to_str(file_path, ft_size_file(file_path));
    tab = ft_split(str_temp);
    free(str_temp);
	if (!(struct_tab = malloc((get_size(tab) + 1) * sizeof(t_line))))
		return (0);
    ft_parse(tab, struct_tab);

    int i = 0;

    while (i < 16)
    {
        printf("%f", struct_tab[i].tps);
        printf("%f", struct_tab[i].speed);
        printf("%f", struct_tab[i].fractionmassique);
        i++;
    }

    free_tab(tab);
    return (0);
}