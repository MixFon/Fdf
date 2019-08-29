/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:14:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/29 16:47:38 by widraugr         ###   ########.fr       */
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

#define KEY_ESC		53
#define KEY_LEFT	123
#define KEY_RIGHT	124
#define KEY_DOWN	125
#define KEY_UP		126
#define KEY_PLUS	69
#define KEY_MINUS	78
#define KEY_H		4
#define KEY_J		38
#define KEY_K		40
#define KEY_L		37
#define KEY_Z		6
#define KEY_X		7
#define KEY_C		8
#define KEY_A		0
#define KEY_S		1
#define KEY_D		2
#define KEY_F		3
#define KEY_V		9
#define KEY_1		83
#define KEY_2		84
#define KEY_3		85

#define	LET fdf->scale
#define	ANGLE 90
#define	DEG(N) M_PI*N/180

#define	ROW_2 fdf->row_2
#define	COL_2 fdf->col_2
#define	DZ fdf->dz
#define	COLOR 15728640 

#define Y_OX(A, B, C) (int)((((A)-ROW_2)*LET)*cos(DEG(C))+((B)*DZ)*sin(DEG(C)))
#define Z_OX(A, B, C) (int)((((A)-ROW_2)*LET)*(-1)*sin(DEG(C))+((B)*DZ)*cos(DEG(C)))

#define X_OZ(A, B, C) (int)(((A))*cos(DEG(C))-((B))*sin(DEG(C)))
#define Y_OZ(A, B, C) (int)(((A))*(1)*sin(DEG(C))+((B))*cos(DEG(C)))

#define X_OY(A, B, C) (int)(((A))*cos(DEG(C))+((B))*sin(DEG(C)))
#define Z_OY(A, B, C) (int)(((A))*(-1)*sin(DEG(C))+((B))*cos(DEG(C)))

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
	int			scale;
	int			row;
	int			col;
	int			dx;
	int			dy;	
	int			dz;
	int			zk;
	int			zp;
	int			row_2;
	int			col_2;
	int			bits_adr;
	int			size_adr;
	int			endian;
	int			alfa;
	int			beta;
	int			gamma;
	int			color;
}				t_fdf;

typedef struct		s_coor
{
	int			x;
	int			y;
	int			z;
	int			color;
}					t_coor;

/*
** File count_args.c
*/
void	init(t_fdf *fdf);
void	sys_err(char *err);
int		press_key(int key, t_fdf *fdf);
void	count_args(int ac, char **av);
/*
** File count_args.c
*/
void	put_map(t_fdf *fdf);
#endif
