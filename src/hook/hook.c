#include "../../cub3d.h"

// Esc w s a d Left Right
int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		close_window(data);
	if (keycode == 13)
		data->keys.w = 1;
	if (keycode == 1)
		data->keys.s = 1;
	if (keycode == 0)
		data->keys.a = 1;
	if (keycode == 2)
		data->keys.d = 1;
	if (keycode == 123)
		data->keys.left = 1;
	if (keycode == 124)
		data->keys.right = 1;
	return (0);
}

int	close_window(t_data *data)
{
	if (!data)
		return (0);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keys.w = 0;
	if (keycode == 1)
		data->keys.s = 0;
	if (keycode == 0)
		data->keys.a = 0;
	if (keycode == 2)
		data->keys.d = 0;
	if (keycode == 123)
		data->keys.left = 0;
	if (keycode == 124)
		data->keys.right = 0;
	return (0);
}

int	render_frame(t_data *data)
{
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
	//raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	init_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, render_frame, data);
}
