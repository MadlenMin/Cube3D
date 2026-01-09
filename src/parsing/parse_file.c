#include "../../cub3d.h"

static int	parse_cfg(char *s, t_data *d)
{
	if (!ft_strncmp(s, "NO ", 3))
		return (parse_tex(&d->no, s + 2));
	if (!ft_strncmp(s, "SO ", 3))
		return (parse_tex(&d->so, s + 2));
	if (!ft_strncmp(s, "WE ", 3))
		return (parse_tex(&d->we, s + 2));
	if (!ft_strncmp(s, "EA ", 3))
		return (parse_tex(&d->ea, s + 2));
	if (!ft_strncmp(s, "F ", 2))
		return (parse_color(&d->floor, s + 1));
	if (!ft_strncmp(s, "C ", 2))
		return (parse_color(&d->ceiling, s + 1));
	return (err("Unknown identifier"));
}

static int	parse_map_line(char *l, t_data *d, int cfg)
{
	if (cfg < 6)
		return (err("Incomplete configuration before map"));
	if (!is_map_line(l))
		return (err("Invalid map line"));
	d->map = map_add(d->map, l);
	return (0);
}

int	parse_helper(int fd, int *map_started, char **l)
{
	trim_nl(*l);
	if (!(*map_started) && !(*l)[0])
	{
		free(*l);
		*l = get_next_line(fd);
		return (1);
	}
	if (!(*map_started) && is_map_line(*l))
		*map_started = 1;
	return (0);
}

int	parse(int fd, t_data *d, int map_started, int cfg)
{
	char	*l;

	l = get_next_line(fd);
	while (l)
	{
		if (parse_helper(fd, &map_started, &l))
			continue ;
		if (!map_started)
		{
			if (parse_cfg(l, d))
				return (free(l), 1);
			cfg++;
		}
		else
			if (parse_map_line(l, d, cfg))
				return (free(l), 1);
		free(l);
		l = get_next_line(fd);
	}
	if (cfg < 6 || !d->map)
		return (free(l), err("Missing data"));
	return (free(l), validate_map(d));
}
