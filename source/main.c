/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 11:22:14 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/20 19:13:32 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	read_first_line(t_fdf *fdf, int fd)
{
	char	*line;
	int		len;

	line = NULL;
	if (!(get_next_line(fd, &line)))
		sys_err("Not first line.\n");
	len = ft_strlen(line);
	if (!(fdf->map = (int **)malloc(sizeof(int *) * (len + 1))))
		sys_err("Error malloc\n");
}

void	read_map(t_fdf *fdf, int ac, char **av)
{
	int		fd;
	char	*line;
	char	**spl;

	line = NULL;
	count_args(ac, av);
	if ((fd = open(av[ac - 1], O_RDONLY, 0)) == -1)
		sys_err("File not found.\n");
	ft_printf("fd = {%d}\n", fd);
	ft_printf("Name map = {%s}\n", av[ac - 1]);
	read_first_line(fdf, fd);
	while (get_next_line(fd, &line))
	{		
		ft_printf("Line = {%s}\n", line);
		spl = ft_strsplit(line, ' ');
		ft_printf("spl = {%s}\n", spl[1]);
		free(line);
	}
	close(fd);
}

int		main(int ac, char **av)
{
	t_fdf fdf;

	ft_printf("ac = {%d}\n", ac);
	read_map(&fdf, ac, av);
	init(&fdf);
	mlx_key_hook(fdf.win_ptr, exit_key, (void*)0);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
