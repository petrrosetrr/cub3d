/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:13:55 by jalease           #+#    #+#             */
/*   Updated: 2021/01/11 15:13:56 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
 * Создаем массив из флагов равный количеству опций до карты
 * На каждой строке одна из функций гарантированно должна уменьшать
 * количество оставшихся параметров или файл невалиден
 * Пустые строки пропускаются и не учитываются
 * Если строка не является ни одним из параметров - файл не валиден
 *
 * Парсинг происходит до строки начала карты для проверки строк после
 * параметров на наличие лишних символов
 *
 * Если где-то происходит ошибка возвращается NULL из парсера
 *
 */


void free_split(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i++]);
	}
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
int is_only_letters(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_isalpha(line[i]) != 1)
			return (0);
		i++;
	}
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
    map->no = NULL;
    map->we = NULL;
    map->ea = NULL;
    map->s = NULL;
    map->map = NULL;
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

char **map_to_arr(char *file_name)
{
	char	*line;
	char	**map;
	int		fd;
	int		amount;
	int		i = 0;

	amount = 0;
	fd = open(file_name, O_RDONLY);
	//TODO: уйня, переписать на подсчет количества \n
	while (get_next_line(fd, &line) > 0)
	{
		amount++;
		free(line);
	}
	amount++;
	printf("amount %d\n", amount);
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

void get_resolution(t_struct *map_struct, char *line)
{
	char **line_arr;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 3) ||!is_only_letters(line_arr[0]) ||
	line_arr[0][0] != 'R')
		return free_split(line_arr);
	if (is_only_digits(line_arr[1]) && is_only_digits(line_arr[2]))
	{
		map_struct->res[0] = ft_atoi(line_arr[1]);
		map_struct->res[1] = ft_atoi(line_arr[2]);
	}
	return free_split(line_arr);
}

void get_textures(t_struct *m_s, char *line)
{
	char **line_arr;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 2) || !is_only_letters(line_arr[0]))
		return free_split(line_arr);
	if ((ft_strncmp("NO", line_arr[0], 2) == 0) && m_s->no == NULL && ft_strlen(line_arr[0]) == 2)
		m_s->no = ft_strdup(line_arr[1]);
	else if (ft_strncmp("SO", line_arr[0], 2) == 0 && m_s->so == NULL && ft_strlen(line_arr[0]) == 2)
		m_s->so = ft_strdup(line_arr[1]);
	else if (ft_strncmp("WE", line_arr[0], 2) == 0 && m_s->we == NULL && ft_strlen(line_arr[0]) == 2)
		m_s->we = ft_strdup(line_arr[1]);
	else if (ft_strncmp("EA", line_arr[0], 2) == 0 && m_s->ea == NULL && ft_strlen(line_arr[0]) == 2)
		m_s->ea = ft_strdup(line_arr[1]);
	else if (ft_strncmp("S", line_arr[0], 2) == 0 && m_s->s == NULL && ft_strlen(line_arr[0]) == 1)
		m_s->s = ft_strdup(line_arr[1]);
	return free_split(line_arr);
}

void get_fc_colors(t_struct *map_struct, char *line)
{
	char **line_arr;
	char **rgb_arr;
	int i;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 2) || !is_only_letters(line_arr[0]))
		return free_split(line_arr);
	rgb_arr = ft_split(line_arr[1], ',');
	i = 0;
	while (i < 3)
	{
		if(!is_only_digits(rgb_arr[i]))
		{
			free_split(line_arr);
			return free_split(rgb_arr);
		}
		else if(ft_strncmp(line_arr[0], "F", 1) == 0 && ft_strlen(line_arr[0]) == 1)
			map_struct->floor[i] = ft_atoi(rgb_arr[i]);
		else if (ft_strncmp(line_arr[0], "C", 1) == 0 && ft_strlen(line_arr[0]) == 1)
			map_struct->ceiling[i] = ft_atoi(rgb_arr[i]);
		i++;
	}
	free_split(line_arr);
	return free_split(rgb_arr);
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

void copy_map(t_struct *map_struct, char **map, int size, int start)
{
    map_struct->map = ft_calloc(sizeof(char*) * (size + 1), 1);
    while (map[start] != NULL)
    {
        map_struct->map[start] = ft_strdup(map[start]);
//        free(map[start]);
        start++;
    }
    map_struct->map[start] = NULL;
    free(map);
}

void *is_valid(t_struct *map_struct)
{
    return map_struct;
}

void *ft_parser(char *file_name)
{
	t_struct *map_struct;
	char **map;
	int i;
    int map_start;

	i = 0;
	map_struct = malloc(sizeof(t_struct));
	map = map_to_arr(file_name);
	set_to_def(map_struct);
    map_start = get_map_start(map);
    while (i < map_start)
    {
        get_resolution(map_struct, map[i]);
        get_textures(map_struct, map[i]);
        get_fc_colors(map_struct, map[i]);
        i++;
    }
	copy_map(map_struct, map, get_map_size(map) - map_start + 1, map_start);
    return is_valid(map_struct);
	//TODO:error handling
}