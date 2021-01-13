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

int free_split(char **arr, int ret_code)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i++]);
	}
	return (ret_code);
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

char **map_to_arr(char *file_name)
{
	char	*line;
	char	**map;
	int		fd;
	int		amount;
	int		i = 0;

	amount = 0;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		amount++;
	close(fd);
	fd = open(file_name, O_RDONLY);
	map = ft_calloc(amount + 1, sizeof(char*));
	while(get_next_line(fd, &line))
		map[i++] = line;
	map[i] = NULL;
	return (map);
	//TODO:error handling
}
int get_resolution(t_struct *map_struct, char *line)
{
	char **line_arr;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 3))
		return free_split(line_arr, 0);
	if (!is_only_letters(line_arr[0]) || line_arr[0][0] != 'R')
		return free_split(line_arr, 0);
	if (is_only_digits(line_arr[1]) && is_only_digits(line_arr[2]))
	{
		map_struct->res[0] = ft_atoi(line_arr[1]);
		map_struct->res[1] = ft_atoi(line_arr[2]);
	}
	return free_split(line_arr, 1);
}
int get_textures(t_struct *map_struct, char *line, char *f_arg)
{
	char **line_arr;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 2))
		return free_split(line_arr, 0);
	if (!is_only_letters(line_arr[0]) || !ft_strncmp(line_arr[0], f_arg, 2))
		return free_split(line_arr, 0);
	if (ft_strncmp("NO", f_arg, 2))
	{
		map_struct->no = ft_strdup(line_arr[1]);
	}
	else if (ft_strncmp("SO", f_arg, 2))
	{
		map_struct->so = ft_strdup(line_arr[1]);
	}
	else if (ft_strncmp("WE", f_arg, 2))
	{
		map_struct->we = ft_strdup(line_arr[1]);
	}
	else if (ft_strncmp("EA", f_arg, 2))
	{
		map_struct->ea = ft_strdup(line_arr[1]);
	}
	else if (ft_strncmp("S ", f_arg, 2))
	{
		map_struct->ea = ft_strdup(line_arr[1]);
	}
	return free_split(line_arr, 1);
}
int get_fc_colors(t_struct *map_struct, char *line, char *f_arg)
{
	char **line_arr;
	char **rgb_arr;
	int i;

	line_arr = ft_split(line, ' ');
	if (!right_args_amount(line_arr, 2))
		return free_split(line_arr, 0);
	if (!is_only_letters(line_arr[0]))
		return free_split(line_arr, 0);
	rgb_arr = ft_split(line_arr[1], ',');
	i = 0;
	while (i < 3)
	{
		if(!is_only_digits(rgb_arr[i]))
		{
			free_split(line_arr, 0);
			return free_split(rgb_arr, 0);
		}
		else if(ft_strncmp(line_arr[0], "F", 1) && f_arg[0] == 'F')
			map_struct->floor[i] = ft_atoi(rgb_arr[i]);
		else if (ft_strncmp(line_arr[0], "C", 1) && f_arg[0] == 'C')
			map_struct->floor[i] = ft_atoi(rgb_arr[i]);
		i++;
	}
	free_split(line_arr, 1);
	return free_split(rgb_arr, 1);
}
int check_map_line(char *line, int flag)
{
	char *str;

	str = (!flag) ? " 1" : " 012NSWE";
	while(line)
	{
		if (!ft_strchr(str, *line))
			return (0);
		line++;
	}
	return (1);
}
int get_map_start(char **map)
{
	int i;
	int map_start;

	i = 0;
	while (map[i] != NULL)
	{
		if(!check_map_line(map[i], 0))
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
//TODO: написать функцию проверяющюю что строка состоит только из пробелов
// или пустая
void *ft_parser(char *file_name)
{
	t_struct *map_struct;
	char **map;
	int i;
	int flags [9];
	int map_start;

	i = 0;
	map_struct = ft_calloc(sizeof(t_struct), 1);;
	map = map_to_arr(file_name);
	map_start = get_map_start(map);
	while (i < map_start)
	{
		if (map[i][0] == '\0')
			i++;
		else if (ft_strnstr(map[i], "R ", ft_strlen(map[i])) != NULL)
		{
			if(!get_resolution(map_struct, map[i]))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "NO", ft_strlen(map[i])) != NULL)
		{
			if(!get_textures(map_struct, map[i], "NO"))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "SO", ft_strlen(map[i])) != NULL)
		{
			if(!get_textures(map_struct, map[i], "SO"))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "WE", ft_strlen(map[i])) != NULL)
		{
			if(!get_textures(map_struct, map[i], "WE"))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "EA", ft_strlen(map[i])) != NULL)
		{
			if(!get_textures(map_struct, map[i], "EA"))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "S ", ft_strlen(map[i])) != NULL)
		{
			if(!get_textures(map_struct, map[i], "S "))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "F ", ft_strlen(map[i])) != NULL)
		{
			if(!get_fc_colors(map_struct, map[i], "F "))
				return (0);
			else
				i++;
		}
		else if (ft_strnstr(map[i], "C ", ft_strlen(map[i])) != NULL)
		{
			if(!get_fc_colors(map_struct, map[i], "C "))
				return (0);
			else
				i++;
		}
		else
			return NULL;
	}
	//TODO:error handling
}