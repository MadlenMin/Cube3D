#include "../../cub3d.h"

static int	parse_cfg(char *s, t_data *d)
{
	printf("alo\n\n");
	if (!ft_strncmp(s, "NO", 2))
		return (parse_tex(&d->no, s + 2));
	if (!ft_strncmp(s, "SO", 2))
		return (parse_tex(&d->so, s + 2));
	if (!ft_strncmp(s, "WE", 2))
		return (parse_tex(&d->we, s + 2));
	if (!ft_strncmp(s, "EA", 2))
		return (parse_tex(&d->ea, s + 2));
	if (!ft_strncmp(s, "F", 1))
		return (parse_color(&d->floor, s + 1));
	if (!ft_strncmp(s, "C", 1))
		return (parse_color(&d->ceiling, s + 1));
	return (err("Unknown identifier"));
}

void	print_data(t_data *d)
{
	int	i;
	i = 0;
	printf("=== CONFIG ===\n");
	printf("NO: %s\n", d->no ? d->no : "NULL");
	printf("SO: %s\n", d->so ? d->so : "NULL");
	printf("WE: %s\n", d->we ? d->we : "NULL");
	printf("EA: %s\n", d->ea ? d->ea : "NULL");
	printf("Floor color: 0x%06X\n", d->floor);
	printf("Ceiling color: 0x%06X\n", d->ceiling);
	printf("Floor color: %d\n", d->floor);
	printf("Ceiling color: %d\n", d->ceiling);

	printf("\n=== MAP ===\n");
	while (d->map && d->map[i])
	{
		printf("%s\n", d->map[i]);
		i++;
	}
	// printf("\n=== PLAYER ===\n");
	// printf("Position: (%d, %d)\n", d->px, d->py);
	// printf("Direction: %c\n", d->dir);
}

int	parse(int fd, t_data *d)
{
	char	*l;
	int		map_started;
	int		cfg;

	map_started = 0;
	cfg = 0;
	l = get_next_line(fd);
	while (l)
	{
		trim_nl(l);
		if (!map_started && !l[0])
		{
			free(l);
			l = get_next_line(fd);
			continue ;
		}
		if (!map_started && is_map_line(l))
			map_started = 1;
		if (!map_started)
		{
			if (parse_cfg(l, d))
				return (free(l), 1);
			cfg++;
		}
		else
		{
			if (!is_map_line(l))
				return (free(l), err("Invalid map line"));
			d->map = map_add(d->map, l);
		}
		free(l);
		l = get_next_line(fd);
	}
	free(l);
	printf("cfg: %d\n", cfg);
	print_data(d);
	if (cfg < 6 || !d->map)
		return (err("Missing data"));
	//return (validate_map(d));
	return (0);
}
