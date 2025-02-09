/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:41:45 by paminna           #+#    #+#             */
/*   Updated: 2021/04/07 20:12:49 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		ft_validator(char **map, int x, int y, int num_lines)
{
	if (x < 0 || y < 0 || x >= num_lines ||
		map[x][y] == '\0' || map[x][y] == ' ')
		return (0);
	if (map[x][y] == '1' || map[x][y] == '3' || map[x][y] == '4')
		return (1);
	if (map[x][y] == '0')
		map[x][y] = '3';
	if (map[x][y] == '2')
		map[x][y] = '4';
	return (ft_validator(map, x, y - 1, num_lines) &&
			ft_validator(map, x, y + 1, num_lines) &&
			ft_validator(map, x - 1, y, num_lines) &&
			ft_validator(map, x + 1, y, num_lines));
}

void	ft_check_last_string(t_data *img)
{
	if (img->map_x == img->size - 1)
		while (img->map_y != img->max_len)
		{
			if (img->map[img->map_x][img->map_y] != '1' ||
			img->map[img->map_x][img->map_y] != ' ')
				ft_errors("wrong map");
			img->map_y++;
		}
}

void	ft_validate(t_data *img)
{
	int res;

	res = -1;
	img->map_x = 0;
	while (img->map_x < img->size)
	{
		img->map_y = 0;
		while (img->map_y < img->max_len)
		{
			if ((img->map[img->map_x][img->map_y] == '0' ||
			img->map[img->map_x][img->map_y] == '2') && res != 0)
				res = ft_validator(img->map, img->map_x, img->map_y, img->size);
			if (res == 0)
				ft_errors("wrong map");
			img->map_y++;
		}
		if (img->map_x++ == img->size)
			ft_check_last_string(img);
	}
}
