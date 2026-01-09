#include "../../cub3d.h"

void	rotate_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = -data->rot_speed * 0.05;
	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}

void	rotate_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	angle = data->rot_speed * 0.05;
	data->dir_x = data->dir_x * cos(angle) - data->dir_y * sin(angle);
	data->dir_y = old_dir_x * sin(angle) + data->dir_y * cos(angle);
	data->plane_x = data->plane_x * cos(angle) - data->plane_y * sin(angle);
	data->plane_y = old_plane_x * sin(angle) + data->plane_y * cos(angle);
}
