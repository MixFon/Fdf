/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:36:23 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/23 17:05:02 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_fdf *fdf)
{
	fdf->row = 0;
	fdf->col = 0;
	fdf->endian = 0;
	fdf->size_adr = WIDTH;
	fdf->bits_adr = 4;
	fdf->color = -1;
	fdf->str = NULL;
	fdf->angle = 0;
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

int		press_key(int key, t_fdf *fdf)
{
	ft_printf("key {%d}\n", key);
	if (key == 53)
		sys_err("Normal exit.\n");
	else if (key == 126)
	{
		fdf->color = 0;
		put_map(fdf);
		fdf->angle += 10;
		//clear_image(fdf);
		fdf->color = -1;
		put_map(fdf);
	}
	else if (key == 125)
	{
		fdf->angle -= 10;
		clear_image(fdf);
		put_map(fdf);
	}
	return (0);
}

void	count_args(int ac, char **av)
{
	if (ac == 1)
		sys_err("Too few arguments.\n\nUse ./fdf name_map.fdf\n");	
	if (ac > 2)
		sys_err("Too many arguments.\n\nUse ./fdf name_map.fdf\n");	
}
