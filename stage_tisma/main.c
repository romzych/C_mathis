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

float ft_fill_tps(char *str)
{
    int i;
    char *temp;

    i = 0;
    if (!(temp = malloc(sizeof(char) * 4)))
        return (0);
    while (i < 4)
    {
        temp[i] = str[i];
        i++;
    }

    return (atof(temp));
}

float ft_fill_speed(char *str)
{
    int i;
    int y;
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
    return (atof(temp));
}

float ft_fill_fractionmassique(char *str)
{
    int i;
    int y;
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
    return (atof(temp));
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

float ft_Mm(float fma)
{
    float fmo;
    float Mm;
    fmo = fma  / (fma + (0.046 / 0.029) * (1 - fma));
    Mm = fma * 0.046 + (1 - fmo) * 0.029;
    return (Mm);
}

float ft_rho(float Mm)
{
    float rho;
    rho = (101325 * Mm) / (8.314 * 293.15); 
    return (rho);
}

float ft_Q(float rho, float speed)
{
    float Q;
    Q = rho * speed * 0.5;
    return (Q);
}

void ft_calcul(t_line *struct_tab, FILE *fd1, FILE *fd2)
{
    int i;
    float Mm;
    float vmoyMm = 0;
    float minMm = 1000;
    float maxMm = -1000;
    float rho;
    float vmoyrho = 0;
    float minrho = 1000;
    float maxrho = -1000;
    float Q;
    float vmoyQ = 0;
    float minQ = 1000;
    float maxQ = -1000;

    i = 1;
    while (i < 16)
    {

        Mm = ft_Mm(struct_tab[i].fractionmassique);
        vmoyMm += ft_Mm(struct_tab[i].fractionmassique);
        rho = ft_rho(Mm);
        vmoyrho += ft_rho(Mm);
        Q = ft_Q(rho, struct_tab[i].speed);
        vmoyQ += ft_Q(rho, struct_tab[i].speed);
        if (Mm < minMm)
            minMm = Mm;
        if (rho < minrho)
            minrho = rho;
        if (Q < minQ)
            minQ = Q;
        if (Mm > maxMm)
            maxMm = Mm;
        if (rho > maxrho)
            maxrho = rho;
        if (Q > maxQ)
            maxQ = Q;
        fprintf(fd1, "-Masse molaire du mélange : %f ; Masse volumique du mélange : %f ; Débit massique du gaz1 : %f\n", Mm, rho, Q);
        i++;
    }
    fprintf(fd2, "-Valeur moyenne : Masse molaire du mélange=%f ; Masse volumique du mélange=%f ; Débit massique du gaz1=%f\n-Valeur min : Masse molaire du mélange=%f ; Masse volumique du mélange=%f ; Débit massique du gaz1=%f\n-Valeur max : Masse molaire du mélange=%f ; Masse volumique du mélange=%f ; Débit massique du gaz1=%f\n", vmoyMm / 15, vmoyrho / 15, vmoyQ / 15, minMm, minrho, minQ, maxMm, maxrho, maxQ);   
}

int main(void)
{
    char *file_path;
    char *str_temp;
	char **tab;
    FILE *fd1;
    FILE *fd2;
    t_line  *struct_tab;

    file_path = "Questions_fortran_C_dataentree.txt";
    str_temp = file_to_str(file_path, ft_size_file(file_path));
    tab = ft_split(str_temp);
    free(str_temp);
	if (!(struct_tab = malloc((15 * sizeof(t_line)))))
		return (0);
    ft_parse(tab, struct_tab);
    free_tab(tab);
    fd1 = fopen("result1.txt", "w");
    fd2 = fopen("result2.txt", "w");
    ft_calcul(struct_tab, fd1, fd2);
    return (0);
}