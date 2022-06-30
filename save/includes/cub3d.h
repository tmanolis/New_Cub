/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:05:41 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 19:34:58 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../includes/get_next_line.h"
# include "../includes/structs.h"

# define _USE_MATH_DEFINES // to enable the use of macro constants such as M_PI
# include <math.h>

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define TITLE "LES TRADUCTRICES INTERPRETES"

// ERROR MESSAGES
# define MSG_WRONG_FILE "Is not an existing .cub file\n"
# define MSG_MISSING_INFO "The .cub file is missing some info.\n"
# define MSG_INVALID_INFO "The infos of this map are invalid.\n"
# define MSG_WRONG_NB_ARG "Correct usage is ./cub3d <map.cub>\n"
# define MSG_DIRECTION "At least one direction is missing or the input is wrong"
# define MSG_FLOOR_CEILING "The floor or ceiling info is wrong or missing."
# define MSG_INVALID_MAP "The map description is either wrong or incomplete."

// KEYS
# define ARROW_TOP 65362
# define ARROW_BOT 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

// MLX
# define W_HEIGHT 512
# define W_WIDTH 1024
# define T_HEIGHT 64 //64 // tjrs à la ligne 4 du .xpm
# define T_WIDTH 64 //64
# define CELL_SIZE 8

// COLORS
# define WHITE 0xFFFFFF
# define PINK 0xE625A1
# define PURPLE 0x67539E
# define BLACK 0x000000

// GAME PHYSICS
# define PLAYER_SIZE 0.15

typedef unsigned long	t_ulong;

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum e_cardinals
{
	NO,
	SO,
	WE,
	EA
};

enum e_map
{
	TILE = '0',
	WALL = '1'
};

// 00_ERR_HANDLING - 00_check_arg.c
int		check_arg(char *arg);

// 01_PARSING - 00_open_file.c
void	create_map_from_cub_file(char *path, t_data *data);
// 01_PARSING - 01_00_retrieve_path_textures.c
int		retrieve_info_in_file(t_data *data, char **map);
// 01_PARSING - 01_01_retrieve_floor_ceiling.c
int		fill_in_the_floor_or_ceiling(t_graphics *graph, char *line, int j);
// 01_PARSING - 02_parse_map_description.c
int		retrieve_map_description(t_data *data, char **map, int i);
// 01_PARSING - 03_check_info_retrieved.c
t_ulong	convert_rgb_to_hex(int *rgb_array);
int		check_info_retrieved(t_graphics *graphics);
// 01_PARSING - 04_check_map_retrieved.c
int		check_map_retrieved(t_map *map, char **map_array);
// 01_PARSING - 05_check_map_borders.c
int		check_top_or_bottom(char **map_array, int i, int j);
int		check_map_sides(t_map *map, char **map_array);
int		check_left_side_is_closed(char **map_array);
int		check_right_side_is_closed(char **map_array);

// 02_EVENTS_HANDLING - 00_handlers.c
int		cross_btn_handler(t_data *data);
int		key_press_handler(int keysym, t_data *data);
int		raycasting_handler(t_data *data);
// 02_EVENTS_HANDLING - 01_hooks.c
void	mlx_loop_and_hooks(t_data data);
// 02_EVENTS_HANDLING - 02_player_moves.c
void	move_forward(t_data *data);
void	move_backward(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void	rotate_sight(t_data *data, double ro_speed);
// 02_EVENTS_HANDLING - 03_player_offset.c
double	player_offset(t_data *data, char letter);

// 03_GRAPHICS - 00_init_window.c
int		init_window(t_data *data);
void	init_img_to_display(t_data *data, t_img *img);
// 03_GRAPHICS - 01_raycasting_init.c
void	init_raycasting_variables(t_data *data, t_raycast *ray, t_map *map, \
	int x);
void	calculate_raydirx_and_stepx(t_raycast *ray, t_map *map);
void	which_distance_if_wall_hit(t_raycast *ray, t_map *map);
void	calculate_wall_specs(t_data *data, t_raycast *ray, t_map *map);
// 03_GRAPHICS - 02_raycasting_engine.c
void	calculate_and_display(t_data *data, t_img *img);
// 03_GRAPHICS - 03_raycasting_utils.c
int		rgb_to_hex(int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	display_background(unsigned long color, t_img *img, int start, int end, int x);
// 03_GRAPHICS - 04_init_textures.c
void	init_textures(t_data *data);

// 04_MINIMAP - 00_display.c
void	draw_a_cell(t_data *data, int beginX, int beginY, int lenX, int lenY, int color);
void	draw_the_2d_map(t_data *data);

// 04_MINIMAP - 01_moves.c
void	move_player(t_data *data, int keysym);
// 04_MINIMAP - 02_utils.c
void	draw_line(void *mlx, void *window, int beginX, int beginY, int endX, int endY, int color);
// 04_MINIMAP - 03_handlers.c
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);

// 05_UTILS - change_orientation_map.c
void	change_orientation_map(t_data *data, char **map_char);
// 05_UTILS - error_exit.c
void	error_exit(t_data *data, char *str);
// 05_UTILS - free_functions.c
void	free_double_array(char **tab);
int		free_for_your_life(t_data *data);
void	free_textures(t_data *data, t_tex tex);
// 05_UTILS - init_data.c
void	init_data(t_data *data);
void	init_raycasting(t_map *map);
// 05_UTILS - utils_functions.c
int		is_a_white_space(char c);
int		print_error(char *str);

#endif