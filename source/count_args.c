/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:36:23 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/23 15:40:10 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_fdf *fdf)
{
	fdf->row = 0;
	fdf->col = 0;
	fdf->endian = 0;
	fdf->size_adr = W_IMG;
	fdf->bits_adr = 4;
	fdf->color = -1;
	fdf->str = NULL;
	fdf->mlx_ptr = mlx_init();
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "Hello fdf");
}

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
}

int		exit_key(int key)
{
	ft_printf("key {%d}\n", key);
	if (key == 53)
		sys_err("Normal exit.\n");
	return (0);
}

void	count_args(int ac, char **av)
{
	if (ac == 1)
		sys_err("Too few arguments.\n\nUse ./fdf name_map.fdf\n");	
	if (ac > 2)
		sys_err("Too many arguments.\n\nUse ./fdf name_map.fdf\n");	
}
