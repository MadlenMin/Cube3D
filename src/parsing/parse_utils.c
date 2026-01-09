#include "../../cub3d.h"

int	err(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void	trim_nl(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_line(char *l)
{
	int	i;

	i = 0;
	if (!l || !l[0])
		return (0);
	while (l[i])
	{
		if (!is_map_char(l[i]) && l[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
