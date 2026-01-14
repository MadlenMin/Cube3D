#include "../../cub3d.h"

void calculate_ray_direction(t_data *data, t_ray *ray, int x )
{
	ray->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->cameraX;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->cameraX;
}
double calculate_perpendiculare_wall_distence(t_ray *ray)
{
	double wall_distence;
	wall_distence = 0;
	if(ray->side == 0)
		wall_distence = ray->side_dist_x - ray->delta_dist_x;
	else
		wall_distence = ray->side_dist_y - ray->delta_dist_y;
	return (wall_distence);
}
void init_dda(t_data *data, t_ray *ray)
{
	if(ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0/ray->ray_dir_x);
	if(ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0/ray->ray_dir_y);
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	if(ray->ray_dir_x > 0 ) //moving right 
	{
		ray->side_dist_x = (ray->map_x + 1 - data->pos_x) * ray->delta_dist_x;
		ray->step_x = 1;
	}
	else //moving left 
	{
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
		ray->step_x = -1;
	}
	if(ray->ray_dir_y > 0)
	{
		ray->side_dist_y = (ray->map_y + 1 - data->pos_y) * ray->delta_dist_y;
		ray->step_y = 1;
	}
	else
	{
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
		ray->step_y = -1;
	}
	ray->hit = 0;
}

void perform_dda(t_data *data, t_ray *ray)
{
	while(!ray->hit)
	{
		if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if(data->map[ray->map_x][ray->map_y] == '1')
		{
			ray->hit = 1;
			break ; 
		}
	}

}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void project_wall(t_data *data, t_ray *ray, int column, double wall_distence)
{
	int draw_start;
	int draw_end;
	double wall_hight;
	int y;

	y = 0;
	if (wall_distence <= 0.0)
		return;
	wall_hight = (double)SCREEN_HEIGHT / wall_distence;

	draw_start = (int)((SCREEN_HEIGHT / 2) - (wall_hight / 2));
	if(draw_start < 0)
		draw_start = 0;
	draw_end = (int)((SCREEN_HEIGHT / 2) + (wall_hight / 2));
	if(draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	while(y < draw_start)
	{
		my_mlx_pixel_put(data, column, y, data->ceiling);
		y++;
	}
	int color = 0xFF0000;
	if(ray->side == 1)
		color = color/2;
	y = draw_start;
	while(y <= draw_end)
	{
		my_mlx_pixel_put(data, column, y, color);
		y++;
	}
	y = draw_end + 1;
	while(y< SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, column, y, data->floor);
		y++;
	}
}

void raycasting(t_data *data)
{
	int colum;
	t_ray ray;
	double wall_distence;

	wall_distence = 0.0;
	colum = 0;
	while (colum < SCREEN_WIDTH)
	{
		calculate_ray_direction(data, &ray, colum);
		init_dda(data, &ray);
		perform_dda(data, &ray);
		wall_distence = calculate_perpendiculare_wall_distence(&ray);
		project_wall(data, &ray, colum, wall_distence);
		colum++;
	}
}
