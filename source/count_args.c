/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:36:23 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/28 17:08:10 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_fdf *fdf)
{
	fdf->row = 0;
	fdf->col = 0;
	fdf->dx = 0;
	fdf->dy = 0;
	fdf->dz = 3;
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
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "Hello fdf");
	fdf->data_adr = mlx_get_data_addr(fdf->img_ptr,
			&fdf->bits_adr, &fdf->size_adr, &fdf->endian);
}

void	sys_err(char *err)
{
	write(2, err, ft_strlen(err));
	exit(0);
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

void	increase_ten(t_fdf *fdf, int *inc, int val)
{
	clear_image(fdf);
	*inc += val;
	ft_printf("inc = [%d]\n", *inc);
	put_map(fdf);
}

void	decrease_ten(t_fdf *fdf, int *dec, int val)
{
	clear_image(fdf);
	*dec -= val;
	ft_printf("dec = [%d]\n", *dec);
	put_map(fdf);
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

void	projection_iso(t_fdf *fdf)
{
	clear_image(fdf);
	fdf->alfa = 20;
	fdf->beta = -50;
	fdf->gamma = -30;
	put_map(fdf);
}

void	projection_parallel(t_fdf *fdf)
{
	clear_image(fdf);
	fdf->alfa = 0;
	fdf->beta = -90;
	fdf->gamma = 0;
	put_map(fdf);
}

void	projection_perpendicular(t_fdf *fdf)
{
	clear_image(fdf);
	fdf->alfa = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	put_map(fdf);
}

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
	return (0);
}

void	count_args(int ac, char **av)
{
	if (ac == 1)
		sys_err("Too few arguments.\n\nUse ./fdf name_map.fdf\n");	
	if (ac > 2)
		sys_err("Too many arguments.\n\nUse ./fdf name_map.fdf\n");	
}
/*
void	clear_image(t_fdf *fdf)
{
	char	*temp;
	int		i;

	temp = fdf->data_adr;
	i = -1;
	while (++i < WIDTH * 4 * HEIGHT)
		temp[i] = 0;
}
*/
