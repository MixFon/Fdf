/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:11:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 16:29:56 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
