#include "../../cub3d.h"

typedef struct s_ray
{
    double ray_dir_x;
    double ray_dir_y;
    double cameraX;

	
    int map_x;
    int map_y;

    int step_x;
    int step_y;

    double side_dist_x;
    double side_dist_y;

    double delta_dist_x;
    double delta_dist_y;

    int hit;
    int side;
} t_ray;

void raycasting(t_data *data)
{
    int colum;
    t_ray ray;

    colum = 0;
    while (colum < SCREEN_WIDTH)
    {
        calculate_ray_direction(data, &ray, colum);
        init_dda(data, &ray);
        perform_dda(data, &ray);
		calculate_wall_distence(data, &ray);
        project_wall(data, &ray, colum);
        colum++;
    }
}


void calculate_ray_direction(t_data *data, t_ray *ray, int x )
{
	ray->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->cameraX;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->cameraX;
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
/*void project_wall(t_data *data, t_ray *ray, int colum)
{

}*/