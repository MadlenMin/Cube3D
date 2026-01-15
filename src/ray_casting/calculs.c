/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminasya <mminasya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:06:06 by mminasya          #+#    #+#             */
/*   Updated: 2026/01/15 21:11:16 by mminasya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	calculate_step_and_side(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x > 0 ) //moving right 
	{
		ray->side_dist_x = (ray->map_x + 1 - data->pos_x) * ray->delta_dist_x;
		ray->step_x = 1;
	}
	else //moving left 
	{
		ray->side_dist_x = (data->pos_x - ray->map_x) * ray->delta_dist_x;
		ray->step_x = -1;
	}
	if (ray->ray_dir_y > 0)
	{
		ray->side_dist_y = (ray->map_y + 1 - data->pos_y) * ray->delta_dist_y;
		ray->step_y = 1;
	}
	else
	{
		ray->side_dist_y = (data->pos_y - ray->map_y) * ray->delta_dist_y;
		ray->step_y = -1;
	}
}

double	calculate_wallX(t_data *data, t_ray *ray, double wall_distence)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = data->pos_y + wall_distence * ray->ray_dir_y;
	else
		wall_x = data->pos_x + wall_distence * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	calculate_ray_direction(t_data *data, t_ray *ray, int x )
{
	ray->cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->cameraX;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->cameraX;
}

double	calculate_perpendiculare_wall_distence(t_ray *ray)
{
	double	wall_distence;

	wall_distence = 0;
	if (ray->side == 0)
		wall_distence = ray->side_dist_x - ray->delta_dist_x;
	else
		wall_distence = ray->side_dist_y - ray->delta_dist_y;
	return (wall_distence);
}
