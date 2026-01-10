#include "../../cub3d.h"

static void	set_plane_ns(t_data *d, double plane)
{
	if (d->dir == 'N')
	{
		d->dir_x = 0;
		d->dir_y = -1;
		d->plane_x = plane;
		d->plane_y = 0;
	}
	else
	{
		d->dir_x = 0;
		d->dir_y = 1;
		d->plane_x = -plane;
		d->plane_y = 0;
	}
}

static void	set_plane_ew(t_data *d, double plane)
{
	if (d->dir == 'E')
	{
		d->dir_x = 1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = plane;
	}
	else
	{
		d->dir_x = -1;
		d->dir_y = 0;
		d->plane_x = 0;
		d->plane_y = -plane;
	}
}

void	assign_direction(t_data *d)
{
	double	plane;

	plane = 0.66;
	if (d->dir == 'N' || d->dir == 'S')
		set_plane_ns(d, plane);
	else
		set_plane_ew(d, plane);
}
