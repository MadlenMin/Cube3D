// #include "../../cub3d.h"

// static int  flood(char **m, int x, int y)
// {
// 	if (x < 0 || y < 0 || !m[y] || !m[y][x] || m[y][x] == ' ')
// 		return (1);
// 	if (m[y][x] == '1')
// 		return (0);
// 	m[y][x] = '1';
// 	return (flood(m, x + 1, y)
// 		|| flood(m, x - 1, y)
// 		|| flood(m, x, y + 1)
// 		|| flood(m, x, y - 1));
// }

// int  validate_map(t_data *d)
// {
// 	int     x, y, p;
// 	char    **cpy;

// 	y = 0;
// 	p = 0;
// 	while (d->map[y])
// 	{
// 		x = 0;
// 		while (d->map[y][x])
// 		{
// 			if (ft_strchr("NSEW", d->map[y][x]))
// 			{
// 				d->px = x;
// 				d->py = y;
// 				d->dir = d->map[y][x];
// 				p++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	if (p != 1)
// 		return (err("Invalid player count"));
// 	cpy = ft_dup_split(d->map);
// 	if (flood(cpy, d->px, d->py))
// 		return (err("Map not closed"));
// 	ft_free_split(cpy);
// 	return (0);
// }
