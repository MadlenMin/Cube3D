#include "../../cub3d.h"

static void	set_dir(t_data *data)
{
	if (data->dir == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (data->dir == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (data->dir == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (data->dir == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

void	start(t_data *data)
{
	struct timeval	time;

	data->mlx = mlx_init();
	if (!data->mlx)
		exit(1);
	data->win = mlx_new_window(
			data->mlx,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			"cub3D");
	if (!data->win)
		exit(1);
	load_all_textures(data);
	data->img = mlx_new_image(
			data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(
			data->img,
			&data->bpp,
			&data->line_length,
			&data->endian);
	ft_memset(&data->keys, 0, sizeof(t_keys));
	data->pos_x = data->px + 0.5;
	data->pos_y = data->py + 0.5;
	data->map[data->py][data->px] = '0';
	set_dir(data);
	data->move_speed = 0.5;
	data->rot_speed = 0.5;
	gettimeofday(&time, NULL);
	data->old_time = time.tv_sec + time.tv_usec / 1000000.0;
	init_hooks(data);
	mlx_loop(data->mlx);
}
