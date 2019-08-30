/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_two_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:00:56 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:57:14 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	perspective(t_fdf *fdf, t_coor *point)
{
	int	zk;
	int	zp;

	zk = fdf->zk;
	zp = fdf->zp;
	if (point->z == zk)
		return ;
	if (fdf->bl)
	{
		point->x = point->x * (zk - zp) / (zk - point->z);
		point->y = point->y * (zk - zp) / (zk - point->z);
	}
	point->x += (WIDTH / 2) + fdf->dx;
	point->y += (HEIGHT / 2) + fdf->dy;
	point->z = point->z - zp;
}

void	print_two_line_oy(t_fdf *fdf, t_coor start, t_coor end)
{
	start.x = X_OY(start.x, start.z, fdf->gamma);
	start.z = Z_OY(start.x, start.z, fdf->gamma);
	end.x = X_OY(end.x, end.z, fdf->gamma);
	end.z = Z_OY(end.x, end.z, fdf->gamma);
	perspective(fdf, &start);
	perspective(fdf, &end);
	ft_draw_line(fdf, start, end);
}

int		skip_point(t_fdf *fdf, t_coor point)
{
	if (point.x > WIDTH * 0.75 || point.x < -WIDTH * 0.75)
		return (1);
	else if (point.y > HEIGHT * 0.75 || point.y < -HEIGHT * 0.75)
		return (1);
	return (0);
}

void	print_two_line_oz(t_fdf *fdf, t_coor start, t_coor end)
{
	start.x = X_OZ(start.x, start.y, fdf->alfa);
	start.y = Y_OZ(start.x, start.y, fdf->alfa);
	if (skip_point(fdf, start))
		return ;
	end.x = X_OZ(end.x, end.y, fdf->alfa);
	end.y = Y_OZ(end.x, end.y, fdf->alfa);
	if (skip_point(fdf, end))
		return ;
	print_two_line_oy(fdf, start, end);
}

/*
** Рисует две линии матрицы, горизонтально вправо и вертикально вниз.
*/

void	print_two_line_ox(t_fdf *fdf, int i, int j)
{
	t_coor	start;
	t_coor	end;
	int		dev;

	dev = 16;
	start.x = (j - COL2) * LET;
	start.y = Y_OX(i, fdf->map[i][j], fdf->beta);
	start.z = Z_OX(i, fdf->map[i][j], fdf->beta);
	start.color = COLOR >> abs(fdf->map[i][j] % dev);
	if (i + 1 < fdf->row)
	{
		end.x = (j - COL2) * LET;
		end.y = Y_OX(i + 1, fdf->map[i + 1][j], fdf->beta);
		end.z = Z_OX(i + 1, fdf->map[i + 1][j], fdf->beta);
		end.color = COLOR >> abs(fdf->map[i + 1][j] % dev);
		print_two_line_oz(fdf, start, end);
	}
	if (j + 1 < fdf->col)
	{
		end.x = (j + 1 - COL2) * LET;
		end.y = Y_OX(i, fdf->map[i][j + 1], fdf->beta);
		end.z = Z_OX(i, fdf->map[i][j + 1], fdf->beta);
		end.color = COLOR >> abs(fdf->map[i][j + 1] % dev);
		print_two_line_oz(fdf, start, end);
	}
}
