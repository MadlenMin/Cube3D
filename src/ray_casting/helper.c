#include "../../cub3d.h"

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