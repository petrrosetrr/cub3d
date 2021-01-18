#include "../cub3d.h"

void struct_init(t_struct *map_struct)
{
	size_t i;

	i = 0;
	while (i < 2)
		map_struct->res[i++] = -1;

	i = 0;
	while (i < 3)
	{
		map_struct->floor[i] = -1;
		map_struct->ceiling[i++] = -1;
	}
	map_struct->map_start = -1;
	map_struct->no = NULL;
	map_struct->we = NULL;
	map_struct->ea = NULL;
	map_struct->so = NULL;
	map_struct->s = NULL;
	map_struct->map = NULL;

}
int is_f_valid(char *file_name)
{
	int i;
	int fd;

	i = ft_strlen(file_name);
	if (i < 5 || file_name[i - 1 ] != 'b' || file_name[i - 2] != 'u' || file_name[i - 3] != 'c' || file_name[i - 4] != '.')
		return (0);
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (0);
	else
		close(fd);
	return (1);
}
int file_to_array(char *file_name, t_struct *map_struct)
{
	int fd;
	int i;
	char c;
	char *line;

	i = 1;
	fd = open(file_name, O_RDONLY);
	while (read(fd, &c, 1))
		i = (c == '\n') ? i + 1 : i;
	map_struct->map = ft_calloc(i + 1, sizeof(char*));
	i = 0;
	close(fd);
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		map_struct->map[i++] = line;
	map_struct->map[i++] = line;
	map_struct->map[i] = NULL;
	close(fd);
	return (1);
}
int is_only_digits (char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}
int get_first_line(char **map)
{
	int i;
	int k;

	i = 0;
	while (map[i] != NULL)
	{
		k = 0;
		while (map[i][k] != '\0')
		{
			if (!(map[i][k] == '1' || map[i][k] == ' '))
				break;
			else
				k++;
		}
		if(map[i][k] == '\0' && ft_strchr(map[i], '1') != NULL)
			return (i);
		i++;
	}
	return (-1);
}
int get_map_start(char **map)
{
	int i;
	int k;
	char *s;
	int start;

	s = " 012NSWE";
	start = get_first_line(map);
	i = start;
	while (map[i] != NULL)
	{
		k = 0;
		while (map[i][k] != '\0')
		{
			if (ft_strchr(s, map[i][k]) == NULL)
				return (-1);
			k++;
		}
		i++;
	}
	return (start);
}
int n_of_lines(char **map)
{
	int i;

	i = 0;
	while (map != NULL && map[i] != NULL)
	{
		i++;
	}
	return (i);
}
int free_array(char **array, int code)
{
	int i;

	i = 0;
	if (array != NULL)
	{
		while(array[i] != NULL)
		{
			free(array[i++]);
		}
		free(array[i]);
		free(array);
	}
	return (code);
}

int get_resolution (t_struct *map_struct, char *line)
{
	char **arr;
	static int flag;

	if (line != NULL && ft_strnstr(line, "R ", ft_strlen(line)) != 0 && flag == 0)
	{
		arr = ft_split(line, ' ');
		if (arr != NULL && ft_strncmp(arr[0], "R", 1) == 0 && ft_strlen(arr[0]) == 1)
		{
			flag = 1;
			if (n_of_lines(arr) == 3)
			{
				if (is_only_digits(arr[1]) && is_only_digits(arr[2]))
				{
					map_struct->res[0] = ft_atoi(arr[1]);
					map_struct->res[1] = ft_atoi(arr[2]);
					return free_array(arr, 1);
				}
			}
		}
		return free_array(arr, 0);
	}
	return (0);
}
int get_fc_colors (t_struct *map_struct, char *line)
{
	char **arr;
	char **rgb_arr;
	static int flag[2];

	if (line != NULL && ft_strnstr(line, "F ", ft_strlen(line)) != 0 && flag[0] == 0)
	{
		arr = ft_split(line, ' ');
		if (arr != NULL && ft_strncmp(arr[0], "F", 1) == 0 && ft_strlen(arr[0]) == 1)
		{
			flag[0] = 1;
			if (n_of_lines(arr) == 2)
			{
				rgb_arr = ft_split(arr[1], ',');
				if (n_of_lines(rgb_arr) == 3)
				{
					map_struct->floor[0] = ft_atoi(rgb_arr[0]);
					map_struct->floor[1] = ft_atoi(rgb_arr[1]);
					map_struct->floor[2] = ft_atoi(rgb_arr[2]);
					free_array(rgb_arr, 1);
					return free_array(arr, 1);
				}
			}
		}
	}
	else if (line != NULL && ft_strnstr(line, "C ", ft_strlen(line)) != 0 && flag[1] == 0)
	{
		arr = ft_split(line, ' ');
		if (arr != NULL && ft_strncmp(arr[0], "C", 1) == 0 && ft_strlen(arr[0]) == 1)
		{
			flag[1] = 1;
			if (n_of_lines(arr) == 2)
			{
				rgb_arr = ft_split(arr[1], ',');
				if (n_of_lines(rgb_arr) == 3)
				{
					map_struct->ceiling[0] = ft_atoi(rgb_arr[0]);
					map_struct->ceiling[1] = ft_atoi(rgb_arr[1]);
					map_struct->ceiling[2] = ft_atoi(rgb_arr[2]);
					free_array(rgb_arr, 1);
					return free_array(arr, 1);
				}
				free_array(rgb_arr, 0);
			}
		}
		return free_array(arr, 0);
	}
	return (0);
}
int get_textures(t_struct *map_struct, char *line)
{
	char **arr;
	static int flag[5];

	if (line != NULL)
	{
		arr = ft_split(line, ' ');
		if (n_of_lines(arr) == 2)
		{
			if(ft_strncmp(arr[0], "NO", 2) == 0 && ft_strlen(arr[0]) == 2 && flag[0] == 0)
			{
				flag[0] = 1;
				map_struct->no = ft_strdup(arr[1]);
				return free_array(arr, 1);
			}
			else if(ft_strncmp(arr[0], "SO", 2) == 0 && ft_strlen(arr[0]) == 2 && flag[1] == 0)
			{
				flag[1] = 1;
				map_struct->so = ft_strdup(arr[1]);
				return free_array(arr, 1);
			}
			else if(ft_strncmp(arr[0], "WE", 2) == 0 && ft_strlen(arr[0]) == 2 && flag[2] == 0)
			{
				flag[2] = 1;
				map_struct->we = ft_strdup(arr[1]);
				return free_array(arr, 1);
			}
			else if(ft_strncmp(arr[0], "EA", 2) == 0 && ft_strlen(arr[0]) == 2 && flag[3] == 0)
			{
				flag[3] = 1;
				map_struct->ea = ft_strdup(arr[1]);
				return free_array(arr, 1);
			}
			else if(ft_strncmp(arr[0], "S", 1) == 0 && ft_strlen(arr[0]) == 1 && flag[4] == 0)
			{
				flag[4] = 1;
				map_struct->s = ft_strdup(arr[1]);
				return free_array(arr, 1);
			}
		}
		return free_array(arr, 0);
	}
	return (0);
}
int is_empty(char *line)
{
	if (*line == '\0')
		return (1);
	else
		return (0);
}

t_struct ft_parser(char *file_name)
{
	t_struct	map_struct;
	int			i;

	struct_init(&map_struct);
	if (!is_f_valid(file_name) || !file_to_array(file_name, &map_struct)
		|| (map_struct.map_start = get_map_start(map_struct.map)) < 8)
	{
		write(2, "Map error\n", ft_strlen("Map error\n"));
		exit(1);
	}
	i = 0;
	while(i < map_struct.map_start)
	{
		if (!(get_resolution(&map_struct, map_struct.map[i])
		|| get_fc_colors(&map_struct, map_struct.map[i])
		|| get_textures(&map_struct, map_struct.map[i])
		|| is_empty(map_struct.map[i])))
		{
			write(2, "Map error\n", ft_strlen("Map error\n"));
			exit(1);
		}
		i++;
	}
	return (map_struct);
}