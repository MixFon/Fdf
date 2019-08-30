/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:07:17 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:21:13 by widraugr         ###   ########.fr       */
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
		temp++;
		spl++;
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
