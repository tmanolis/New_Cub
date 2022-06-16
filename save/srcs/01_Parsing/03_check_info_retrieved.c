#include "cub3d.h"

// QUAND TOUT EST REMPLI DANS LA STRUCT, ON DOIT CHECKER QUE LES INFOS NE SONT PAS
// ABERRANTES (ex le path qui doit exister, les valeurs du RGB qui doivent aller 
// de 0 à 256)

static int	check_input_of_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("The following number is invalid : ", 2);
			ft_putnbr_fd(rgb[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("RGB has a min value of 0 and a max value of 255.\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_existence_of_path(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		close(fd);
		ft_putstr_fd("The following path is invalid : ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (FAILURE);
	}
	return (SUCCESS);
}	

int	check_info_retrieved(t_graphics *graphics)
{
	// printf("dis donc\n");
	// printf("VOICI LES DONNEES RECUP :\nDirections: NO : %s | SO : %s | WE : %s | EA : %s\n", graphics->dir_NO, graphics->dir_SO, graphics->dir_WE, graphics->dir_EA);
	// if (graphics->floor)
	// {
	// 	for (int k = 0; k < 3; k++)
	// 		printf("floor: %d => |%d|\n", k, graphics->floor[k]);
	// }
	// if (graphics->ceiling)
	// {
	// 	for (int l = 0; l < 3; l++) // PB avec le 0, qui est genre la "fin" du int * et du coup s'imprime pas
	// 		printf("ceiling: %d => |%d|\n", l, graphics->ceiling[l]);
	// }
	if (!graphics->dir_NO || !graphics->dir_SO || !graphics->dir_WE
		|| !graphics->dir_EA || !graphics->floor || !graphics->ceiling)
		return (FAILURE);
	if (check_existence_of_path(graphics->dir_NO) == FAILURE
		|| check_existence_of_path(graphics->dir_SO) == FAILURE
		|| check_existence_of_path(graphics->dir_WE) == FAILURE
		|| check_existence_of_path(graphics->dir_EA) == FAILURE
		|| check_input_of_rgb(graphics->floor) == FAILURE
		|| check_input_of_rgb(graphics->ceiling) == FAILURE)
		return (FAILURE);
	printf("tout est bon!\n");
	return (SUCCESS);
}