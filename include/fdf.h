/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:14:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/23 14:49:01 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

#define	WIDTH 1920
#define	HEIGHT 1080

#define	W_IMG 1000
#define	H_IMG 500

#define	LET 10
#define	DEB 0.7
#define	DEG(N) M_PI*N/180
#define X(A, B, C) (int)(A*cos(DEG(C))+B*sin(DEG(C)))
#define Y(A, B, C) (int)(-A*sin(DEG(C))+B*cos(DEG(C)))

# define ABS(N) ((N<0)?(-N):(N))

typedef struct	s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	int			**map;
	char		*str;
	char		**arr;
	char		*data_adr;
	int			col;
	int			row;
	int			bits_adr;
	int			size_adr;
	int			endian;
	int			color;
}				t_fdf;

typedef struct		s_coor
{
	double			x;
	double			y;
}					t_coor;

/*
** File count_args.c
*/
void	init(t_fdf *fdf);
void	sys_err(char *err);
int		exit_key(int key);
void	count_args(int ac, char **av);

#endif
