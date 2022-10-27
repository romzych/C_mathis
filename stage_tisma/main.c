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

int main(void)
{
    char *file_path;
    char *str_temp;
	char **tab;

    file_path = "Questions_fortran_C_dataentree.txt";
    str_temp = file_to_str(file_path, ft_size_file(file_path));
    tab = ft_split(str_temp);
	ft_putstr(tab[0]);
    return (0);
}