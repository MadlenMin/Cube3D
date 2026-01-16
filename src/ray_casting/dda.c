/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminasya <mminasya@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:06:13 by mminasya          #+#    #+#             */
/*   Updated: 2026/01/16 23:13:17 by mminasya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_dda(t_data *data, t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	ray->map_x = (int)data->pos_x;
	ray->map_y = (int)data->pos_y;
	calculate_step_and_side(data, ray);
	ray->hit = 0;
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
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
			|| (int)ft_strlen(data->map[ray->map_y]) <= ray->map_x
			|| data->map[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
			break ;
		}
	}
}
