/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 03:33:01 by jalease           #+#    #+#             */
/*   Updated: 2021/02/13 04:49:41 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H

void		struct_init(t_struct *map_struct);
int			is_f_valid(char *file_name);
int			file_to_array(char *file_name, t_struct *map_struct);
int			is_only_digits(char *line);
int			get_first_line(char **map);
int			get_map_start(char **map);
int			n_of_lines(char **map);
int			free_array(char **array, int code);
void		set_map_size(t_struct *map_struct);
t_struct	ft_parser(char *file_name);
int			is_empty(char *line);
int			get_fc_colors(t_struct *map_struct, char *line);
#endif
