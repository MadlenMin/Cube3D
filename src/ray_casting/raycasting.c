#include "../../cub3d.h"

void raycasting(t_data *data)
{
	int colum;
	double wall_distence;

	wall_distence = 0.0;
	colum = 0;
	while (colum < SCREEN_WIDTH)
	{
		calculate_ray_direction(data, data->ray, colum);
		init_dda(data, data->ray);
		perform_dda(data, data->ray);
		wall_distence = calculate_perpendiculare_wall_distence(data->ray);
		project_wall(data, data->ray, colum, wall_distence);
		colum++;
	}
}