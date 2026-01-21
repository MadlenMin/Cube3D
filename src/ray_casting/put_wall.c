/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminasya <mminasya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:05:50 by mminasya          #+#    #+#             */
/*   Updated: 2026/01/16 22:26:31 by mminasya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	draw_wall(t_data *data, t_project *project, int column, int y)
{
	double	color;

	project->tex_y = (int)project->tex_pos & (TEXTURE_HEIGHT - 1);
	project->tex_pos += project->step;
	color = data->tex[project->tex_idx].addr[TEXTURE_HEIGHT
		* project->tex_y + project->tex_x];
	if (data->ray->side == 1)
		color = color - 0.5;
	my_mlx_pixel_put(data, column, y, color);
}

t_project	*init_project(t_data *data, t_project *project, t_ray *ray,
	double wall_distence)
{
	project->wall_hight = (double)SCREEN_HEIGHT / wall_distence;
	project->draw_start = (int)((SCREEN_HEIGHT / 2)
			- (project->wall_hight / 2));
	if (project->draw_start < 0)
		project->draw_start = 0;
	project->draw_end = (int)((SCREEN_HEIGHT / 2) + (project->wall_hight / 2));
	if (project->draw_end >= SCREEN_HEIGHT)
		project->draw_end = SCREEN_HEIGHT - 1;
	project->wall_x = calculate_wallx(data, ray, wall_distence);
	project->tex_x = (int)(project->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		project->tex_x = TEXTURE_WIDTH - project->tex_x - 1;
	project->tex_idx = get_tex_index(ray);
	project->step = 1.0 * TEXTURE_HEIGHT / project->wall_hight;
	project->tex_pos = (project->draw_start - SCREEN_HEIGHT
			/ 2 + project->wall_hight / 2) * project->step;
	return (project);
}

void	project_wall(t_data *data, t_ray *ray, int column, double wall_distence)
{
	t_project	project;
	int			y;

	y = 0;
	init_project(data, &project, ray, wall_distence);
	while (y < project.draw_start)
	{
		my_mlx_pixel_put(data, column, y, data->ceiling);
		y++;
	}
	y = project.draw_start;
	while (y <= project.draw_end)
	{
		draw_wall(data, &project, column, y);
		y++;
	}
	y = project.draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(data, column, y, data->floor);
		y++;
	}
}
