#include "../../cub3d.h"

void	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->dir_x * data->move_speed * 0.1;
	new_y = data->pos_y + data->dir_y * data->move_speed * 0.1;
	if(data->map[(int)new_y][(int)new_x] != '1')
	{
		if (data->map[(int)data->pos_y][(int)new_x] == '0')
			data->pos_x = new_x;
		if (data->map[(int)new_y][(int)data->pos_x] == '0')
			data->pos_y = new_y;
	}
}

void	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x - data->dir_x * data->move_speed * 0.1;
	new_y = data->pos_y - data->dir_y * data->move_speed * 0.1;
	if (data->map[(int)data->pos_y][(int)new_x] == '0')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] == '0')
		data->pos_y = new_y;
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x - data->plane_x * data->move_speed * 0.1;
	new_y = data->pos_y - data->plane_y * data->move_speed * 0.1;
	if (data->map[(int)data->pos_y][(int)new_x] == '0')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] == '0')
		data->pos_y = new_y;
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->pos_x + data->plane_x * data->move_speed * 0.1;
	new_y = data->pos_y + data->plane_y * data->move_speed * 0.1;
	if (data->map[(int)data->pos_y][(int)new_x] == '0')
		data->pos_x = new_x;
	if (data->map[(int)new_y][(int)data->pos_x] == '0')
		data->pos_y = new_y;
}
