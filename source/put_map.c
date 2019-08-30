/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:50:19 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:24:32 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	put_status(t_fdf *fdf)
{
	char *massage[4];
	char *num;

	num = ft_itoa(fdf->beta);
	massage[0] = "Angles:";
	massage[1] = "        alfa";
	massage[2] = "        beta";
	massage[3] = "        gamma";
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 490, YELLOW, massage[0]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 520, YELLOW, massage[1]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 240, 520, YELLOW, num);
	free(num);
	num = ft_itoa(fdf->gamma);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 550, YELLOW, massage[2]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 240, 550, YELLOW, num);
	free(num);
	num = ft_itoa(fdf->alfa);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 580, YELLOW, massage[3]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 240, 580, YELLOW, num);
	free(num);
	if (fdf->bl)
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 260, 130, YELLOW, "(on)");
	else
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 260, 130, YELLOW, "(off)");
}

void	put_strings(t_fdf *fdf)
{
	char	*massage[11];
	int		i;
	int		coor_x;
	int		coor_y;

	i = -1;
	coor_x = 50;
	coor_y = 130;
	massage[0] = "Perspective        Q";
	massage[1] = "Move               H J K L";
	massage[2] = "Rotate             UP RIGHT LEFT DOWN";
	massage[3] = "Kamera             D F";
	massage[4] = "Projection         A S";
	massage[5] = "Height of peaks    C V";
	massage[6] = "Scale              + -";
	massage[7] = "Views:";
	massage[8] = "       isometry    1";
	massage[9] = "       parallel    2";
	massage[10] = "       normal      3";
	while (++i < 11)
	{
		mlx_string_put(fdf->mlx_ptr, fdf->win_ptr,
				coor_x, coor_y, YELLOW, massage[i]);
		coor_y += 30;
	}
}

void	put_coordinate(t_fdf *fdf)
{
	char *massage[3];
	char *num;

	num = ft_itoa(fdf->dx);
	massage[0] = "Coordinate:";
	massage[1] = "        X";
	massage[2] = "        Y";
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 630, YELLOW, massage[0]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 660, YELLOW, massage[1]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 240, 660, YELLOW, num);
	free(num);
	num = ft_itoa(fdf->dy);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 50, 690, YELLOW, massage[2]);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 240, 690, YELLOW, num);
	free(num);
}

void	put_size(t_fdf *fdf)
{
	char *num;
	char *temp;

	temp = ft_itoa(fdf->zk);
	num = ft_multi_strdup(3, "(", temp, ")");
	free(temp);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 280, 220, YELLOW, num);
	free(num);
	temp = ft_itoa(fdf->zp);
	num = ft_multi_strdup(3, "(", temp, ")");
	free(temp);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 280, 250, YELLOW, num);
	free(num);
	temp = ft_itoa(fdf->dz);
	num = ft_multi_strdup(3, "(", temp, ")");
	free(temp);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 280, 280, YELLOW, num);
	free(num);
	temp = ft_itoa(fdf->scale);
	num = ft_multi_strdup(3, "(", temp, ")");
	free(temp);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 280, 310, YELLOW, num);
	free(num);
}

/*
** Вывод на экран ортогональную  матрицу.
*/

void	put_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->row)
	{
		j = -1;
		while (++j < fdf->col)
			print_two_line_ox(fdf, i, j);
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	if (fdf->hide)
	{
		put_strings(fdf);
		put_status(fdf);
		put_coordinate(fdf);
		put_size(fdf);
	}
}
