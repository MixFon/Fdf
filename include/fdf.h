/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:14:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/20 19:13:35 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include "../ft_printf/ft_printf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <mlx.h>

#define	WIDTH 1024
#define	HEIGHT 600

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			**map;
}				t_fdf;
/*
** File count_args.c
*/
void	init(t_fdf *fdf);
void	sys_err(char *err);
int		exit_key(int key);
void	count_args(int ac, char **av);

#endif
