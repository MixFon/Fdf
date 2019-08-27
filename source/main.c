/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:22:14 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/27 17:28:48 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/*
** Подсчет колличества чисел в одном ряду.
*/

int		count_numbers(char **spl)
{
	int		len;
	char	**temp;

	len = 0;
	temp = spl;
	while (*temp != NULL)
	{
		len++;
		temp++;
	}
	return (len);
}

void	dell_arr(char **spl)
{
	char **temp;	

	temp = spl;
	while (*temp != NULL)
	{
		ft_strdel(temp);
		temp++;
	}
	free(spl);
}

/*
** Копирует в массив интов.
*/

void	copy_number(int *num, char **spl)
{
	int *temp;

	temp = num;
	while (*spl != NULL)
	{
		*temp = ft_atoi(*spl);
		ft_printf("temp = {%d}\n", *temp);
		temp++;	   
		spl++;
	}
}

void	print_map(t_fdf *fdf)
{
	int i;
	int j;

	i = -1;
	while(++i < fdf->row) 
	{
		j = -1;
		while(++j < fdf->col) 
			ft_printf("%5d", fdf->map[i][j]);
		ft_putchar('\n');
	}
}

/*
** Удаляем массив.
*/

void	dell_map(t_fdf *fdf)
{
	int **temp;

	temp = fdf->map;
	while (*temp != NULL)
	{
		free(*temp);
		temp++;
	}
	free(fdf->map);
}

/*
** Обрабатываем большую строку, .
*/

void	working_string(t_fdf *fdf)
{
	fdf->arr = ft_strsplit(fdf->str, '\n');
	if (!(fdf->map = (int **)malloc(sizeof(int *) * (fdf->row + 1))))
		sys_err("Error malloc\n");
	fdf->map[fdf->row] = NULL;
}

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
	ft_printf("Name map = {%s}\n", fdf->str);
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
		ft_printf("str = {%s}\n", fdf->arr[i]);
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

	count_args(ac, av);
	if ((fd = open(av[ac - 1], O_RDONLY, 0)) == -1)
		sys_err("File not found.\n");
	ft_printf("fd = {%d}\n", fd);
	ft_printf("Name map = {%s}\n", av[ac - 1]);
	one_big_string(fdf, fd);
	working_string(fdf);
	write_map_int(fdf);
	fdf->row_2 = fdf->row / 2;
	fdf->col_2 = fdf->col / 2;
	print_map(fdf);
	//dell_map(fdf);
	close(fd);
}

/*
** Функция рисует линию.
*/

void	put_pixel_adr(t_fdf *fdf, int x, int y)
{
	int i;

	if (x >= WIDTH || y >= HEIGHT || x <= 0 || y <= 0)
		return ;
	i = (x * fdf->bits_adr / 8) + (y * fdf->size_adr);
	fdf->data_adr[i] = fdf->color;
	fdf->data_adr[++i] = fdf->color >> 8;
	fdf->data_adr[++i] = fdf->color >> 16;
	fdf->data_adr[++i] = 0;
}

void	ft_draw_line_source(t_coor *delta, t_coor *sign, t_coor point1,
		t_coor point2)
{
	(*delta).x = ABS((point2.x - point1.x));
	(*delta).y = ABS((point2.y - point1.y));
	(*sign).x = (point1.x < point2.x) ? 1 : -1;
	(*sign).y = (point1.y < point2.y) ? 1 : -1;
}

/*
** Функция рисует линию.
*/

void	ft_draw_line(t_fdf *fdf, t_coor point1,
		t_coor point2)
{
	t_coor		delta;
	t_coor		sign;
	int		error;
	int		error2;

	ft_draw_line_source(&delta, &sign, point1, point2);
	error = delta.x - delta.y;
	put_pixel_adr(fdf, point2.x, point2.y);
	while (point1.x != point2.x || point1.y != point2.y)
	{
		put_pixel_adr(fdf, point1.x, point1.y);
		error2 = error * 2;
		if (error2 > -delta.y)
		{
			error -= delta.y;
			point1.x += sign.x;
		}
		if (error2 < delta.x)
		{
			error += delta.x;
			point1.y += sign.y;
		}
	}
}

/*
** Пересчитывает координаты для идомутрического вида.
*/

static void iso(t_fdf *fdf, int *x, int *y, int z)
{
    int prev_x;
    int prev_y;

    prev_x = *x;
    prev_y = *y;
    *x = (prev_x - prev_y) * cos(DEG(fdf->alfa)) + (WIDTH / 2) + fdf->dx;
    *y = (-z * LET) + (prev_x + prev_y) * sin(DEG(fdf->gamma)) + (HEIGHT / 2) + fdf->dy;
}

void	print_two_line_oy(t_fdf *fdf, t_coor start, t_coor end)
{

	start.x = X_OY(start.x, start.z, fdf->gamma) + (WIDTH / 2) + fdf->dx; 
	start.y += (HEIGHT / 2) + fdf->dy;
	start.z = Z_OY(start.x, start.z, fdf->gamma);
	end.x = X_OY(end.x, end.z, fdf->gamma) + (WIDTH / 2) + fdf->dx; 
	end.y += (HEIGHT / 2) + fdf->dy;
	end.z = Z_OY(end.x, end.z, fdf->gamma);
	ft_draw_line(fdf, start, end);
}

void	print_two_line_oz(t_fdf *fdf, t_coor start, t_coor end)
{

	start.x = X_OZ(start.x, start.y, fdf->alfa);// + (WIDTH / 2) + fdf->dx; 
	start.y = Y_OZ(start.x, start.y, fdf->alfa);// + (HEIGHT / 2) + fdf->dy;
	end.x = X_OZ(end.x, end.y, fdf->alfa);// + (WIDTH / 2) + fdf->dx; 
	end.y = Y_OZ(end.x, end.y, fdf->alfa);// + (HEIGHT / 2) + fdf->dy;
	print_two_line_oy(fdf, start, end);
}

/*
** Рисует две линии матрицы, горизонтально вправо и вертикально вниз.
*/

void	print_two_line_ox(t_fdf *fdf, int i, int j)
{
	t_coor	start;
	t_coor	end;

	start.x = (j - COL_2) * LET;
	start.y = Y_OX(i, fdf->map[i][j], fdf->beta);
	start.z = Z_OX(i, fdf->map[i][j], fdf->beta);
	if (i + 1 < fdf->row)
	{
		end.x = (j - COL_2) * LET;
		end.y = Y_OX(i + 1, fdf->map[i + 1][j], fdf->beta);
		end.z = Z_OX(i + 1, fdf->map[i + 1][j], fdf->beta);
		print_two_line_oz(fdf, start, end);
	}
	if (j + 1 < fdf->col)
	{
		end.x = (j + 1 - COL_2) * LET ;
		end.y = Y_OX(i, fdf->map[i][j + 1], fdf->beta);
		end.z = Z_OX(i, fdf->map[i][j + 1], fdf->beta);
		print_two_line_oz(fdf, start, end);
	}
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

	ft_printf("ac = {%d}\n", ac);
	init(&fdf);
	mlx_key_hook(fdf.win_ptr, press_key, &fdf);
	read_map(&fdf, ac, av);
	calculation_scale(&fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
