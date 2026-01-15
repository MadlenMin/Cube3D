#include "../../cub3d.h"

double calculate_wallX(t_data *data, t_ray *ray, double wall_distence)
{
	double wall_x;
	
	if (ray->side == 0)
		   wall_x = data->pos_y + wall_distence * ray->ray_dir_y;
	else
		   wall_x = data->pos_x + wall_distence * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return(wall_x);
}
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

/*void calculate_step_and_side()
{

}*/

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
		if (ray->map_y < 0 || ray->map_x < 0 || !data->map[ray->map_y]
			|| (int)ft_strlen(data->map[ray->map_y]) <= ray->map_x)
		{
			ray->hit = 1;
			break ;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
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

int get_tex_index(t_ray *ray)
{
    if (ray->side == 0) // Vertical wall hit (East or West face)
    {
        if (ray->ray_dir_x > 0)
            return (TEX_EA); // Ray moving right hits East-facing (West side) wall
        else
            return (TEX_WE); // Ray moving left hits West-facing (East side) wall
    }
    else // Horizontal wall hit (North or South face)
    {
        if (ray->ray_dir_y > 0)
            return (TEX_SO); // Ray moving down hits South-facing (North side) wall
        else
            return (TEX_NO); // Ray moving up hits North-facing (South side) wall
    }
}

void draw_wall(t_data *data, t_project *project, int column, int y)
{
	unsigned int color;

	project->tex_y = (int)project->tex_pos & (TEXTURE_HEIGHT - 1);
    project->tex_pos += project->step;
    color = data->tex[project->tex_idx].addr[TEXTURE_HEIGHT * project->tex_y + project->tex_x];
    if (data->ray->side == 1)
        color = (color >> 1) & 8355711;
    my_mlx_pixel_put(data, column, y, color);
}

t_project *init_project(t_data *data, t_project *project, t_ray *ray, double wall_distence)
{
	project->wall_hight = (double)SCREEN_HEIGHT / wall_distence;
	project->draw_start = (int)((SCREEN_HEIGHT / 2) - (project->wall_hight / 2));
	if(project->draw_start < 0)
		project->draw_start = 0;
	project->draw_end = (int)((SCREEN_HEIGHT / 2) + (project->wall_hight / 2));
	if(project->draw_end >= SCREEN_HEIGHT)
		project->draw_end = SCREEN_HEIGHT - 1;
	project->wall_x = calculate_wallX(data, ray, wall_distence);
	project->tex_x = (int)(project->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
    	project->tex_x = TEXTURE_WIDTH - project->tex_x - 1;
	project->tex_idx = get_tex_index(ray);
    project->step = 1.0 * TEXTURE_HEIGHT / project->wall_hight;
	project->tex_pos = (project->draw_start - SCREEN_HEIGHT / 2 + project->wall_hight / 2) * project->step;
	return(project);
}

void project_wall(t_data *data, t_ray *ray, int column, double wall_distence)
{
	t_project project;
	int y;

	y = 0;
	init_project(data, &project, ray, wall_distence);
	while(y < project.draw_start)
	{
		my_mlx_pixel_put(data, column, y, data->ceiling);
		y++;
	}
	y = project.draw_start;
	while(y <= project.draw_end)
	{
        draw_wall(data, &project,column,y);
		y++;
	}
	y = project.draw_end + 1;
	while(y< SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, column, y, data->floor);
		y++;
	}
}


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

/*void project_wall(t_data *data, t_ray *ray, int column, double wall_distence)
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

	double wall_x = calculate_wallX(data, ray, wall_distence);
	// 2. Calculate texX (which column of pixels in the texture)
	int tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
    	tex_x = TEXTURE_WIDTH - tex_x - 1;
	int tex_idx = get_tex_index(ray);

	// 3. Calculate how much to increase the texture coordinate per screen pixel
    double step = 1.0 * TEXTURE_HEIGHT / wall_hight;

	double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + wall_hight / 2) * step;

	while(y < draw_start)
	{
		my_mlx_pixel_put(data, column, y, data->ceiling);
		y++;
	}
	y = draw_start;
	while(y <= draw_end)
	{
        int tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
        tex_pos += step;
        unsigned int color = data->tex[tex_idx].addr[TEXTURE_HEIGHT * tex_y + tex_x];

        // Optional: darken colors of one side
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
        my_mlx_pixel_put(data, column, y, color);
		y++;
	}
	y = draw_end + 1;
	while(y< SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, column, y, data->floor);
		y++;
	}
}*/