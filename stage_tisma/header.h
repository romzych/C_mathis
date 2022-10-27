#ifndef HEADER_H
# define HEADER_H


#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

# define BUF_SIZE 16384

typedef struct	s_line
{
	int	tps;
	int	speed;
	int	fractionmassique;
}				t_line;

int ft_size_file(char *file_path);
int		ft_strlen_count(char *str, char *charset, int i);
int		ft_count_word(char *str, char *charset);
int		ft_cmp(char str, char *charset);
void	ft_fill_tab(char **tab, char *str, char *charset, int wordnbr);
char *file_to_str(char *file_path, int file_size);
char	**ft_split(char *str);
void ft_putstr(char *str);

#endif