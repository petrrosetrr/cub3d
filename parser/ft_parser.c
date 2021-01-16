#include "../cub3d.h"

void set_to_def (t_struct *map)
{
    int i;
    i = 0;
    while (i < 2)
        map->res[i++] = -1;
    i = 0;
    while (i < 3)
    {
        map->floor[i] = -1;
        map->ceiling[i++] = -1;
    }
    map->map_size = -1;
    map->no = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->so = NULL;
    map->s = NULL;
    map->map = NULL;
}
char **map_to_arr(char *file_name)
{
    char	*line;
    char	**map;
    int		fd;
    int		amount;
    int		i = 0;

    amount = 1;
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        amount++;
        free(line);
    }
    free(line);
    close(fd);
    fd = open(file_name, O_RDONLY);
    map = ft_calloc(amount + 1, sizeof(char*));
    while(get_next_line(fd, &line))
        map[i++] = line;
    map[i++] = line;
    map[i] = NULL;
    return (map);
    //TODO:error handling
}
int get_map_size(char **map)
{
    int i;

    i = 0;
    while (map[i] != NULL)
    {
        i++;
    }
    return (--i);
}
int free_td_array(char **arr, int ret_code)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
    {
        free(arr[i++]);
    }
    free(arr[i]);
    free(arr);
    return (ret_code);
}
int check_map_line(char *line, int flag)
{
    char *str;
    int i;

    i = 0;
    str = (!flag) ? " 1" : " 012NSWE";
    while(line[i] != '\0')
    {
        if (!ft_strchr(str, *line))
            return (0);
        i++;
    }
    if (*line == '\0')
        return (0);
    return (1);
}
int get_map_start(char **map)
{
    int i;
    int map_start;
    i = 0;
    while (map[i] != NULL)
    {
        if(!check_map_line(map[i], 0) || ft_strnstr(map[i], "1", ft_strlen(map[i])) == NULL)
        {
            i++;
        }
        else
        {
            map_start = i;
            while(map[i] != NULL)
            {
                if (!check_map_line(map[i], 1))
                    return (0);
                i++;
            }
            return (map_start);
        }
    }
    return (0);
}
int check_empty_line(char *line)
{
    if (*line != '\0')
        return (0);
    return (1);
}
int right_args_amount(char **array, int d)
{
    int i;

    i = 0;
    while (array[i] != NULL)
        i++;
    if (i != d)
        return (0);
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
int check_file_name (char *file_name)
{
    int i;

    i = ft_strlen(file_name);
    if (i < 5 || file_name[i - 1 ] != 'b' || file_name[i - 2] != 'u' || file_name[i - 3] != 'c' || file_name[i - 4] != '.')
        return (0);
    return (1);
}
void copy_map(t_struct *map_struct, char **map, int size, int start)
{
	int i;

	i = 0;
	map_struct->map = ft_calloc(sizeof(char*) * (size + 1), 1);
	while (map[start] != NULL)
	{
		map_struct->map[i] = ft_strdup(map[start]);
		start++;
		i++;
	}
	map_struct->map[start] = NULL;
}
void free_map(char **map)
{
	int i;

	i = 0;

	while (map[i] != NULL)
		free(map[i++]);
	free(map[i]);
	free(map);
}
int is_t(char *line)
{
	char *arr[5];
	int i;

	i = 0;
	arr[0] = "NO";
	arr[1] = "SO";
	arr[2] = "WE";
	arr[3] = "EA";
	arr[4] = "S";
	while (i < 5)
	{
		if (ft_strncmp(arr[i++], line, ft_strlen(line)) == 0)
			return (1);
	}
	return (0);
}


int get_resolution(t_struct *map_struct, char *line)
{
    char **line_arr;
    static int flag;

    line_arr = ft_split(line, ' ');
    if (ft_strncmp(line_arr[0], "R", ft_strlen(line_arr[0])) != 0 || flag != 0 || !right_args_amount(line_arr, 3))
        return free_td_array(line_arr, 0);
    flag++;
    if (is_only_digits(line_arr[1]) && is_only_digits(line_arr[2])) {
        map_struct->res[0] = ft_atoi(line_arr[1]);
        map_struct->res[1] = ft_atoi(line_arr[2]);
		return free_td_array(line_arr, 1);
    }
	return free_td_array(line_arr, 0);
}
int get_fc_colors(t_struct *map_struct, char *line)
{
    char **line_arr;
    char **rgb_arr;
    int i;
    static int flags[2];

    line_arr = ft_split(line, ' ');
    if (!right_args_amount(line_arr, 2))
        return free_td_array(line_arr, 0);
    i = 0;
    if (ft_strncmp(line_arr[0],"F", ft_strlen(line_arr[0])) == 0 && flags[0]++ == 0)
    {
    	printf("F fccolors\n");
		rgb_arr = ft_split(line_arr[1], ',');
        while(i < 3)
        {
            if(!is_only_digits(rgb_arr[i]))
                return free_td_array(rgb_arr, 0) && free_td_array(line_arr, 0);
            map_struct->floor[i] = ft_atoi(rgb_arr[i]);
            i++;
        }
		return (free_td_array(rgb_arr, 1) && free_td_array(line_arr, 1));
    }
    else if (ft_strncmp(line_arr[0],"C", ft_strlen(line_arr[0])) == 0 && flags[1]++ == 0)
    {
		printf("C fccolors\n");
		rgb_arr = ft_split(line_arr[1], ',');
        while(i < 3)
        {
            if(!is_only_digits(rgb_arr[i]))
                return free_td_array(rgb_arr, 0) && free_td_array(line_arr, 0);
            map_struct->ceiling[i] = ft_atoi(rgb_arr[i]);
            i++;
        }
		return (free_td_array(rgb_arr, 1) && free_td_array(line_arr, 1));
    }
    return (free_td_array(line_arr, 0));
}
int set_texture(char **var, char **line_arr)
{
	*var = ft_strdup(line_arr[1]);
	return free_td_array(line_arr, 1);
}
int get_textures(t_struct *m_s, char *line)
{
    char **line_arr;
    static int flags[5];

    line_arr = ft_split(line, ' ');
    if (!right_args_amount(line_arr, 2) || !is_t(line_arr[0]))
        return free_td_array(line_arr, 0);
    if (ft_strncmp("NO", line_arr[0], ft_strlen(line_arr[0])) == 0 && flags[0]++ == 0)
		return set_texture(&m_s->no, line_arr);
    else if (ft_strncmp("SO", line_arr[0], 2) == 0 && ft_strlen(line_arr[0]) == 2 && flags[1]++ == 0)
		return set_texture(&m_s->so, line_arr);
    else if (ft_strncmp("WE", line_arr[0], ft_strlen(line_arr[0])) == 0 && flags[2]++ == 0)
		return set_texture(&m_s->we, line_arr);
    else if (ft_strncmp("EA", line_arr[0], ft_strlen(line_arr[0])) == 0 && flags[3]++ == 0)
		return set_texture(&m_s->ea, line_arr);
    else if (ft_strncmp("S", line_arr[0], ft_strlen(line_arr[0])) == 0 && flags[4]++ == 0)
		return set_texture(&m_s->s, line_arr);
    return free_td_array(line_arr, 0);
}

int is_textures_valid(t_struct map_struct)
{
	if (open(map_struct.no, O_RDONLY) < 0
	|| open(map_struct.so, O_RDONLY) < 0
	|| open(map_struct.we, O_RDONLY) < 0
	|| open(map_struct.ea, O_RDONLY) < 0
	|| open(map_struct.s, O_RDONLY) < 0)
		return (0);
	return (1);
}
int is_fcr_valid(t_struct map_struct)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (map_struct.floor[i] < 0 || map_struct.ceiling [i] < 0)
			return (0);
		i++;
	}
	if (map_struct.res[0] < 0 || map_struct.res[1] < 0)
		return (0);
	return (1);
}

//int check_map_borders(char **map)
//{
//
//}
//int is_map_valid (char **map)
//{
//	int i, k;
//
//	i = 0;
//	while (map[i] != NULL)
//	{
//		k = 0;
//		while (map[i][k])
//		{
//			if (i == 0 || i == get_map_size(map))
//			{
//				if (!(map[i][k] == ' ' || map[i][k] == '1'))
//					return (0);
//			}
//			else
//			{
//
//			}
//			k++;
//		}
//		i++;
//	}
//	return (1);
//}

//int is_valid(t_struct map_struct)
//{
//	if (!is_fcr_valid(map_struct))
//		return (0);
//	if (!is_textures_valid(map_struct))
//		return (0);
//	if (!is_map_valid(map_struct.map))
//		return (0);
//	return (1);
//}

void *ft_parser(char *file_name)
{
    t_struct *map_struct;
    char **map;
    int i;
    int map_start;

    i = 0;
    if (!check_file_name(file_name))
        return (NULL);
    map_struct = malloc(sizeof(t_struct));
    map = map_to_arr(file_name);
    set_to_def(map_struct);
    if ((map_start = get_map_start(map)) < 8)
	{
		write(2, "Map error\n", ft_strlen("Map error\n"));
		exit(1);
	}
    map_struct->map_size = get_map_size(map) - map_start + 1;
    copy_map(map_struct, map, map_struct->map_size, map_start);
    while (i < map_start)
    {
        if (!(get_resolution(map_struct, map[i]) ||
              get_textures(map_struct, map[i]) ||
              get_fc_colors(map_struct, map[i]) ||
              check_empty_line(map[i])))
		{
        	write(2, "Map error\n", ft_strlen("Map error\n"));
        	exit(1);
		}
        i++;
    }
    free_map(map);
    return map_struct;
    //TODO:error handling
}