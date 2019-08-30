/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:14:00 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:29:44 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	projection_view(t_fdf *fdf, int key)
{
	if (key == KEY_1)
		projection_iso(fdf);
	else if (key == KEY_2)
		projection_parallel(fdf);
	else if (key == KEY_3)
		projection_perpendicular(fdf);
}

void	len_dz(t_fdf *fdf, int key)
{
	if (key == KEY_C)
		increase_ten(fdf, &fdf->dz, 1);
	else if (key == KEY_V)
		decrease_ten(fdf, &fdf->dz, 1);
}

void	perspective_size(t_fdf *fdf, int key)
{
	if (key == KEY_A)
		increase_ten(fdf, &fdf->zp, 100);
	else if (key == KEY_S)
		decrease_ten(fdf, &fdf->zp, 100);
	else if (key == KEY_D)
		increase_ten(fdf, &fdf->zk, 100);
	else if (key == KEY_F)
		decrease_ten(fdf, &fdf->zk, 100);
}

void	press_qw(t_fdf *fdf, int key)
{
	if (key == KEY_Q)
		inversion(fdf, &fdf->bl);
	else if (key == KEY_W)
		inversion(fdf, &fdf->hide);
}

int		press_key(int key, t_fdf *fdf)
{
	ft_printf("key {%d}\n", key);
	if (key == KEY_ESC)
		sys_err("Normal exit.\n");
	else if (key == KEY_UP || key == KEY_DOWN ||
			key == KEY_RIGHT || key == KEY_LEFT ||
			key == KEY_Z || key == KEY_X)
		rotation_map(fdf, key);
	else if (key == KEY_PLUS || key == KEY_MINUS)
		scale_map(fdf, key);
	else if (key == KEY_H || key == KEY_J || key == KEY_K || key == KEY_L)
		move_map(fdf, key);
	else if (key == KEY_1 || key == KEY_2 || key == KEY_3)
		projection_view(fdf, key);
	else if (key == KEY_C || key == KEY_V)
		len_dz(fdf, key);
	else if (key == KEY_A || key == KEY_S || key == KEY_D || key == KEY_F)
		perspective_size(fdf, key);
	else if (key == KEY_Q || key == KEY_W)
		press_qw(fdf, key);
	return (0);
}
