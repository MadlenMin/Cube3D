#include "../../cub3d.h"

static void	init_mlx(t_data *d)
{
	d->mlx = mlx_init();
	if (!d->mlx)
		exit(1);
	d->win = mlx_new_window(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!d->win)
		exit(1);
	d->img = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->line_length, &d->endian);
}

static void	init_player(t_data *d)
{
	d->pos_x = d->px + 0.5;
	d->pos_y = d->py + 0.5;
	d->map[d->py][d->px] = '0';//playerin 0 acrec 
	assign_direction(d);
	d->move_speed = 0.5;
	d->rot_speed = 0.5;
	ft_memset(&d->keys, 0, sizeof(t_keys));
	d->ray = malloc(sizeof(t_ray));
	if (!d->ray)
		exit(1);
}

void	start(t_data *d)
{
	init_mlx(d);
	load_all_textures(d);
	init_player(d);
	init_hooks(d);
	mlx_loop(d->mlx);
}
