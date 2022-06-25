#include "cub3d.h"

void	mlx_loop_and_hooks(t_data data)
{
	mlx_loop_hook(data.mlx, &raycasting_handler, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press_handler, &data);
	mlx_hook(data.win, ClientMessage, LeaveWindowMask, &cross_btn_handler, &data);
	mlx_loop(data.mlx);
}

