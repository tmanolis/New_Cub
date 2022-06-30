/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:21:48 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 20:22:53 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_graphics
{
	char				*dir_no;
	char				*dir_so;
	char				*dir_we;
	char				*dir_ea;
	int					*floor;
	unsigned long		hex_floor;
	int					*ceiling;
	unsigned long		hex_ceiling;
}				t_graphics;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct s_tex
{
	t_img	ea;
	t_img	we;
	t_img	no;
	t_img	so;
}				t_tex;

typedef struct s_map
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			nb_line;
	char		**map;
	char		**map_marc;
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

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		mapx;
	int		mapy;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	double	wall_x;
	int		draw_start;
	int		draw_end;
	int		color;
}				t_raycast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_graphics	graphics;
	t_map		map;
	t_img		img;
	t_tex		tex;
	t_raycast	ray;
	int			pixel;
}				t_data;

#endif