/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalease <jalease@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:13:43 by jalease           #+#    #+#             */
/*   Updated: 2021/01/11 15:13:47 by jalease          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char *argv[])
{
	if (argc == 2 || argc == 3)
	{
		t_struct *map = (t_struct*)ft_parser(argv[1]);

	}
	else
	{
		//error
	}
	return (0);
}
