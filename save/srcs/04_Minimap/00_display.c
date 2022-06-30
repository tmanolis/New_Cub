#include "cub3d.h"

/*
	"We need to retrieve a pixel at some x and y coordinates, 
	but we're dealing with a one dimensional array.
	The formula to get the right index  is : index = line_len * y + x * (bpp / 8)"
	
	=> We're creating our own mlx_pixel_put because "the mlx_pixel_put function 
	basically draws the pixel on the window directly, without waiting for the 
	whole background to be drawn = ugly flickering on the screen"
*/

// dessine les cubes collés les un aux autres
void	draw_a_cell(t_data *data, int beginX, int beginY, int lenX, int lenY, int color)
{
	int	i;
	int	j;

	i = 1;
	while (i < lenX)
	{
		j = 1;
		while (j < lenY)
		{
			my_mlx_pixel_put(&data->img, beginX + i, beginY + j, color);
			j++;
		}
		i++;
	}
}

// // avec les i et j set à 1, on a un petit espace esthetique entre chaque cube
// static void	draw_a_cell2(t_data *data, int beginX, int beginY, int lenX, int lenY, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < lenX)
// 	{
// 		j = 0;
// 		while (j < lenY)
// 		{
// 			my_mlx_pixel_put(&data->img, beginX + i, beginY + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }


static void	draw_player_pos(t_data *data)
{
	draw_a_cell(data, data->map.p_x * CELL_SIZE, data->map.p_y * CELL_SIZE, CELL_SIZE, CELL_SIZE, PINK);
}

/**
 * @brief Displays on screen the minimap (top-down view) with the player in it
 * 		
 * 		 Steps:
 * 		 - Loops through the two dimensional array of the map
 * 		 - If the cell is a wall (== '1') : draws the cell in white
 * 		 - Else draws the floor in purple
 * 		 - At the end, draws the player position over
 * 
 * @param data 
 */
void	draw_the_2d_map(t_data *data)
{
	int i;
	size_t j;

	i = 0;
	while (i < data->map.nb_line)
	{
		j = 0;
		while (j < ft_strlen(data->map.map[i]))
		{
			if (data->map.map[i][j] == '1')
			{
				draw_a_cell(data, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
			}
			// else if (data->map.map[i][j] == '0')
			// 	draw_a_cell2(data, j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, PURPLE);
			j++;
		}
		i++;
	}
	draw_player_pos(data);
}