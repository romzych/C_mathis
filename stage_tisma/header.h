#ifndef HEADER_H
# define HEADER_H


#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


# define BUF_SIZE 16384

typedef struct	s_line
{
	float	tps;
	float	speed;
	float	fractionmassique;
}				t_line;

int ft_size_file(char *file_path);
int		ft_strlen_count(char *str, char *charset, int i);
int		ft_count_word(char *str, char *charset);
int		ft_cmp(char str, char *charset);
void	ft_fill_tab(char **tab, char *str, char *charset, int wordnbr);
char *file_to_str(char *file_path, int file_size);
char	**ft_split(char *str);
void ft_putstr(char *str);
void	free_tab(char **tab);
char *file_to_str(char *file_path, int file_size);
float ft_fill_tps(char *str);
float ft_fill_speed(char *str);
float ft_fill_fractionmassique(char *str);
void ft_parse(char **tab, t_line *struct_tab);
float ft_Mm(float fma);
float ft_rho(float Mm);
float ft_Q(float rho, float speed);
void ft_calcul(t_line *struct_tab, FILE *fd1, FILE *fd2);




#endif