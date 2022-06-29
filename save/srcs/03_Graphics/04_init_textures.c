#include "cub3d.h"

void	init_tex(t_data *data, char *tex_path, t_img *tex_img)
{
	tex_img->mlx_img = mlx_xpm_file_to_image(data->mlx, tex_path,
			&tex_img->x, &tex_img->y);
	if (!tex_img->mlx_img)
		error_exit(data, "Creation of texture image has failed");
	tex_img->addr = mlx_get_data_addr(tex_img->mlx_img, &tex_img->bits_per_pixel,
			&tex_img->line_length, &tex_img->endian);
	if (tex_img->mlx_img == NULL || tex_img->addr == NULL)
		error_exit(data, "The initialization of texture_dress has failed\n");
}


void	init_textures(t_data *data)
{
    // appeler fill_textures
	init_tex(data, data->graphics.dir_NO, &data->tex.no);
	init_tex(data, data->graphics.dir_SO, &data->tex.so);
	init_tex(data, data->graphics.dir_EA, &data->tex.ea);
	init_tex(data, data->graphics.dir_WE, &data->tex.we);
}