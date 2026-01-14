#include "../../cub3d.h"




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
static void debug_perform_dda(t_data *data, t_ray *ray)
{
	int step_count = 0;

    printf("=== DEBUG DDA START ===\n");
    printf("Ray dir: (%.3f, %.3f)\n", ray->ray_dir_x, ray->ray_dir_y);
    printf("Player pos: (%.3f, %.3f)\n", data->pos_x, data->pos_y);
    printf("Start cell: (%d, %d)\n\n", ray->map_x, ray->map_y);

	while(!ray->hit)
	{
		printf("Step %d\n", step_count);
        printf("  Cell: (%d, %d)\n", ray->map_x, ray->map_y);
        printf("  side_dist_x: %.3f | side_dist_y: %.3f\n",
               ray->side_dist_x, ray->side_dist_y);

			   if(ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
			 printf("  -> Step in X direction\n");
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
			 printf("  -> Step in Y direction\n");
		}
		if(data->map[ray->map_x][ray->map_y] == '1')
		{
			ray->hit = 1;
			printf("  HIT WALL at (%d, %d)\n", ray->map_x, ray->map_y);
            printf("  Hit side: %s\n", ray->side == 0 ? "VERTICAL (X)" : "HORIZONTAL (Y)");
			//break ; 
		}
		    step_count++;
			if (step_count > 100)
        {
            printf("ERROR: DDA did not terminate!\n");
            break;
        }

        printf("\n");
	}
	  printf("=== DEBUG DDA END ===\n\n");

}
void debug_ray_dda(t_data *data, t_ray *ray)
{
	int step_count = 0;

	while (!ray->hit)
    {
		
		if (ray->side_dist_x < ray->side_dist_y)
        {
			ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
            printf("  -> Step in X direction\n");
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
            printf("  -> Step in Y direction\n");
        }
		
        if (data->map[ray->map_x][ray->map_y] == '1')
        {
            ray->hit = 1;
            printf("  HIT WALL at (%d, %d)\n", ray->map_x, ray->map_y);
            printf("  Hit side: %s\n", ray->side == 0 ? "VERTICAL (X)" : "HORIZONTAL (Y)");
        }
		
        step_count++;
        if (step_count > 100)
        {
            printf("ERROR: DDA did not terminate!\n");
            break;
        }

        printf("\n");
    }

    printf("=== DEBUG DDA END ===\n\n");
}
		void raycasting(t_data *data)
		{
			int colum;
			t_ray ray;
		
			colum = 0;
			while (colum < SCREEN_WIDTH)
			{
				calculate_ray_direction(data, &ray, colum);
				init_dda(data, &ray);
				//perform_dda(data, &ray);
				debug_perform_dda(data, &ray);
				//calculate_wall_distence(data, &ray);
				//project_wall(data, &ray, colum);
				colum++;
			}
		}
