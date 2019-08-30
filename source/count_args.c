/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:36:23 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:29:26 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_fdf *fdf)
{
	fdf->row = 0;
	fdf->col = 0;
	fdf->dx = 0;
	fdf->dy = 0;
	fdf->dz = 1;
	fdf->bl = 1;
	fdf->hide = 1;
	fdf->zk = 3000;
	fdf->zp = 500;
	fdf->row_2 = 0;
	fdf->col_2 = 0;
	fdf->endian = 0;
	fdf->size_adr = WIDTH;
	fdf->bits_adr = 4;
	fdf->scale = 1;
	fdf->color = -1;
	fdf->str = NULL;
	fdf->alfa = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->mlx_ptr = mlx_init();
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "Fdf");
	fdf->data_adr = mlx_get_data_addr(fdf->img_ptr,
			&fdf->bits_adr, &fdf->size_adr, &fdf->endian);
}

/*
** Move map to up, right, left, down.
*/

void	move_map(t_fdf *fdf, int key)
{
	if (key == KEY_H)
		decrease_ten(fdf, &fdf->dx, 10);
	else if (key == KEY_K)
		decrease_ten(fdf, &fdf->dy, 10);
	else if (key == KEY_J)
		increase_ten(fdf, &fdf->dy, 10);
	else if (key == KEY_L)
		increase_ten(fdf, &fdf->dx, 10);
}

void	rotation_map(t_fdf *fdf, int key)
{
	if (key == KEY_DOWN)
		increase_ten(fdf, &fdf->beta, 10);
	else if (key == KEY_UP)
		decrease_ten(fdf, &fdf->beta, 10);
	else if (key == KEY_RIGHT)
		increase_ten(fdf, &fdf->gamma, 10);
	else if (key == KEY_LEFT)
		decrease_ten(fdf, &fdf->gamma, 10);
	else if (key == KEY_Z)
		increase_ten(fdf, &fdf->alfa, 10);
	else if (key == KEY_X)
		decrease_ten(fdf, &fdf->alfa, 10);
}

void	scale_map(t_fdf *fdf, int key)
{
	if (key == KEY_PLUS)
		increase_ten(fdf, &fdf->scale, 1);
	else if (key == KEY_MINUS)
		decrease_ten(fdf, &fdf->scale, 1);
}
