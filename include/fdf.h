/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:14:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/21 15:39:20 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <mlx.h>

#define	WIDTH 1920
#define	HEIGHT 1080

#define	LET 10

# define ABS(N) ((N<0)?(-N):(N))

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			**map;
	char		*str;
	char		**arr;
	int			col;
	int			row;
}				t_fdf;

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

/*
** File count_args.c
*/
void	init(t_fdf *fdf);
void	sys_err(char *err);
int		exit_key(int key);
void	count_args(int ac, char **av);

#endif
