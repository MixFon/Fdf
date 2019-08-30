/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_adr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:56:12 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 17:20:45 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	count_args(int ac)
{
	if (ac == 1)
		sys_err("Too few arguments.\n\nUse ./fdf name_map.fdf\n");
	if (ac > 2)
		sys_err("Too many arguments.\n\nUse ./fdf name_map.fdf\n");
}

void	inversion(t_fdf *fdf, int *inv)
{
	clear_image(fdf);
	*inv = !(*inv);
	put_map(fdf);
}

void	clear_image(t_fdf *fdf)
{
	char	*temp;
	int		i;

	temp = fdf->data_adr;
	i = -1;
	while (++i < WIDTH * 4 * HEIGHT)
		temp[i] = 0;
}

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

/*
** Функция рисует линию.
*/

void	put_pixel_adr(t_fdf *fdf, t_coor point)
{
	int i;

	if (point.x >= WIDTH || point.y >= HEIGHT || point.x <= 0 || point.y <= 0)
		return ;
	i = (point.x * fdf->bits_adr / 8) + (point.y * fdf->size_adr);
	fdf->data_adr[i] = point.color;
	fdf->data_adr[++i] = point.color >> 8;
	fdf->data_adr[++i] = point.color >> 16;
	fdf->data_adr[++i] = 0;
}
