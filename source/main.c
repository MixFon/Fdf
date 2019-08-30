/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:22:14 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 17:16:11 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	one_big_string(t_fdf *fdf, int fd)
{
	char	*line;
	char	*temp;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		temp = fdf->str;
		fdf->str = ft_multi_strdup(3, fdf->str, line, "\n");
		ft_strdel(&temp);
		ft_strdel(&line);
		fdf->row++;
	}
	ft_strdel(&line);
}

void	write_map_int(t_fdf *fdf)
{
	char	**spl;
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (fdf->arr[++i] != NULL)
	{
		spl = ft_strsplit(fdf->arr[i], ' ');
		len = count_numbers(spl);
		if (fdf->col != len && fdf->col != 0)
			sys_err("Error map.\n");
		fdf->col = len;
		if (!(fdf->map[i] = (int *)malloc(sizeof(int) * (len))))
			sys_err("Error malloc\n");
		copy_number(fdf->map[i], spl);
		dell_arr(spl);
	}
	dell_arr(fdf->arr);
}

void	read_map(t_fdf *fdf, int ac, char **av)
{
	int		fd;

	count_args(ac);
	if ((fd = open(av[ac - 1], O_RDONLY, 0)) == -1)
		sys_err("File not found.\n");
	one_big_string(fdf, fd);
	working_string(fdf);
	write_map_int(fdf);
	fdf->row_2 = fdf->row / 2;
	fdf->col_2 = fdf->col / 2;
	close(fd);
}

void	calculation_scale(t_fdf *fdf)
{
	while (fdf->scale * fdf->row < HEIGHT - 200 &&
			fdf->scale * fdf->col < WIDTH - 800)
		fdf->scale++;
	ft_printf("scale = {%d}\n", fdf->scale);
}

int		main(int ac, char **av)
{
	t_fdf fdf;

	init(&fdf);
	mlx_key_hook(fdf.win_ptr, press_key, &fdf);
	read_map(&fdf, ac, av);
	calculation_scale(&fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
