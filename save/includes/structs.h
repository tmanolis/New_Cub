#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_graphics
{
	char	*dir_NO;
	char	*dir_SO;
	char	*dir_WE;
	char	*dir_EA;
	int		*floor;
	int		*ceiling;
}				t_graphics;

typedef struct	s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct s_map
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			nb_line;
	char		**map;
	int			index_end_of_map;
	char		p_direction;
	int			p_x;
	int			p_y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rotate_speed;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_graphics	graphics;
	t_map		map;
	t_img		img;

}				t_data;

#endif