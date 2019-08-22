/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:22:14 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/22 16:28:57 by widraugr         ###   ########.fr       */
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
	print_map(fdf);
	dell_map(fdf);
	close(fd);
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

void	ft_draw_line(void *mlx_ptr, void *win_ptr, t_coor point1,
		t_coor point2)
{
	t_coor delta;
	t_coor	sign;
	int		error;
	int		error2;

	ft_draw_line_source(&delta, &sign, point1, point2);
	error = delta.x - delta.y;
	mlx_pixel_put(mlx_ptr, win_ptr, point2.x, point2.y, 0xBF2956);
	while (point1.x != point2.x || point1.y != point2.y)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, point1.x, point1.y, 0xBF2956);
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

void	print_two_line(t_fdf *fdf, int i, int j)
{
	t_coor	start;
	t_coor	end;

	//start.x = j * LET;
	//start.y = i * LET;
	start.x = X(j * LET, i * LET, 45) + WIDTH / 2;
	start.y = Y(j * LET, i * LET, 45) + HEIGHT / 2;
	if (i + 1 < fdf->row)
	{
		//end.x = j * LET;
		//end.y = (i + 1) * LET;
		end.x = X(j * LET, (i + 1) * LET, 45) + WIDTH / 2;
		end.y = Y(j * LET, (i + 1) * LET, 45) + HEIGHT / 2;
		ft_draw_line(fdf->mlx_ptr, fdf->win_ptr, start, end);
	}
	if (j + 1 < fdf->col)
	{
		//end.x = (j + 1) * LET ;
		//end.y = i * LET;
		end.x = X((j + 1) * LET, i * LET, 45) + WIDTH / 2;
		end.y = Y((j + 1) * LET, i * LET, 45) + HEIGHT / 2;
		ft_draw_line(fdf->mlx_ptr, fdf->win_ptr, start, end);
	}
}

/*
** Вывод на экран ортогональную  матрицу.
*/

void	put_map(t_fdf *fdf)
{
	int	**map;
	int	i;
	int	j;

	map = fdf->map;
	i = -1;
	while (++i < fdf->row)
	{
		j = -1;
		while (++j < fdf->col)
			print_two_line(fdf, i, j);
	}
}

void	put_line(t_fdf *fdf)
{
	t_coor	start;
	t_coor	end;
	double	deg;

	ft_printf("%f\n", cos(DEG(60)));
	start.x = 0;
	start.y = 0;
	end.x = 100;
	end.y = 200;
	ft_draw_line(fdf->mlx_ptr, fdf->win_ptr, start, end);
	start.x = X(0, 0, 45);
	start.y = Y(0, 0, 45);
	end.x = X(100, 200, 45);
	end.y = Y(100, 200, 45);
	//end.x = 212;
	//end.y = 70;
	ft_printf("x = {%f} y = {%f}\n", end.x, end.y);
	ft_draw_line(fdf->mlx_ptr, fdf->win_ptr, start, end);
}

int		main(int ac, char **av)
{
	t_fdf fdf;

	ft_printf("ac = {%d}\n", ac);
	init(&fdf);
	mlx_key_hook(fdf.win_ptr, exit_key, (void*)0);
	read_map(&fdf, ac, av);
	//put_line(&fdf);
	put_map(&fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
