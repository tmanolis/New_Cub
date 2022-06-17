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

#define _USE_MATH_DEFINES // to enable the use of macro constants such as M_PI
#include <math.h>

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define TITLE "Les Traductrices Interpretes"

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
# define CELL_SIZE 8

// COLORS
# define WHITE 0xFFFFFF
# define PINK 0xE625A1
# define PURPLE 0x67539E
# define BLACK 0x000000

enum e_output
{ 
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};


extern int	worldMap[24][24];
// 00_ERR_HANDLING - 00_check_arg.c
int		check_arg(char *arg);

// 01_PARSING - 00_open_file.c
void	create_map_from_cub_file(char *path, t_data *data);
// 01_PARSING - 01_retrieve_info_in_file.c
int		retrieve_info_in_file(t_data *data, char **map);
// 01_PARSING - 02_parse_map_description.c
int		retrieve_map_description(t_data *data, char **map, int i);
// 01_PARSING - 03_check_info_retrieved.c
int		check_info_retrieved(t_graphics *graphics);
// 01_PARSING - 04_check_map_retrieved.c
int		check_map_retrieved(t_map *map, char **map_array);
// 01_PARSING - 05_check_map_borders.c
int		check_top_or_bottom(char **map_array, int i, int j);
int		check_map_sides(t_map *map, char **map_array);
int		check_left_side_is_closed(char **map_array);
int		check_right_side_is_closed(char **map_array);

// 02_EVENTS_HANDLING - 00_handlers.c
int		handle_crossbtn(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		key_press(int keysym, t_data *data);
// 02_EVENTS_HANDLING - 01_hooks.c
void	mlx_loop_and_hooks(t_data data);
// 02_EVENTS_HANDLING - 02_player_moves.c
void	move_player(t_data *data, int keysym);

// 03_GRAPHICS - 00_init_window.c
int		init_window(t_data *data);
void	draw_line(void *mlx, void *window, int beginX, int beginY, int endX, int endY, int color);
int		render(t_data *data);
void	draw_the_2d_map(t_data *data);
// 03_GRAPHICS - 02_raycasting_engine.c
int		raycasting_loop(t_data *data);
// 03_GRAPHICS - 04_2d_map.c
void	draw_a_cell(t_data *data, int beginX, int beginY, int lenX, int lenY, int color);

// 05_UTILS - free_functions.c
void	free_double_array(char **tab);
int		free_for_your_life(t_data *data);
// 05_UTILS - init_data.c
void	init_data(t_data *data);
void	init_raycasting(t_map *map);
// 05_UTILS - utils_functions.c
int		is_a_white_space(char c);
int		print_error(char *str);


void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif