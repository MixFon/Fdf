/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: widraugr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 12:14:10 by widraugr          #+#    #+#             */
/*   Updated: 2019/08/30 17:20:47 by widraugr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

# define KEY_ESC		53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_DOWN	125
# define KEY_UP		126
# define KEY_PLUS	69
# define KEY_MINUS	78
# define KEY_H		4
# define KEY_J		38
# define KEY_K		40
# define KEY_L		37
# define KEY_Z		6
# define KEY_X		7
# define KEY_C		8
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_F		3
# define KEY_V		9
# define KEY_Q		12
# define KEY_W		13
# define KEY_1		83
# define KEY_2		84
# define KEY_3		85

# define LET fdf->scale
# define YELLOW 0xFFFFF0
# define DEG(N) M_PI*N/180

# define ROW2 fdf->row_2
# define COL2 fdf->col_2
# define DZ fdf->dz
# define COLOR 0xFFFF00

# define Y_OX(A, B, C) (int)((((A)-ROW2)*LET)*cos(DEG(C))+((B)*DZ)*sin(DEG(C)))
# define Z_OX(A, B, C) (int)((-((A)-ROW2)*LET)*sin(DEG(C))+((B)*DZ)*cos(DEG(C)))

# define X_OZ(A, B, C) (int)(((A))*cos(DEG(C))-((B))*sin(DEG(C)))
# define Y_OZ(A, B, C) (int)(((A))*(1)*sin(DEG(C))+((B))*cos(DEG(C)))

# define X_OY(A, B, C) (int)(((A))*cos(DEG(C))+((B))*sin(DEG(C)))
# define Z_OY(A, B, C) (int)(((A))*(-1)*sin(DEG(C))+((B))*cos(DEG(C)))

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
	int			bl;
	int			hide;
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

typedef struct	s_coor
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_coor;

/*
** File count_args.c
*/
void			move_map(t_fdf *fdf, int key);
void			rotation_map(t_fdf *fdf, int key);
void			scale_map(t_fdf *fdf, int key);
void			init(t_fdf *fdf);
/*
** File put_map.c
*/
void			put_status(t_fdf *fdf);
void			put_size(t_fdf *fdf);
void			put_coordinate(t_fdf *fdf);
void			put_strings(t_fdf *fdf);
void			put_map(t_fdf *fdf);
/*
** File draw_line_adr.c
*/
double			percent(int start, int end, int current);
int				get_light(int start, int end, double percentage);
int				get_color(t_coor current, t_coor start, t_coor end,
		t_coor delta);
t_coor			ft_draw_line_source(t_coor *delta, t_coor *sign, t_coor point1,
		t_coor point2);
void			ft_draw_line(t_fdf *fdf, t_coor point1, t_coor point2);
/*
** File put_pixel_adr.c
*/
void			count_args(int ac);
void			inversion(t_fdf *fdf, int *inv);
void			clear_image(t_fdf *fdf);
void			sys_err(char *err);
void			put_pixel_adr(t_fdf *fdf, t_coor point);
/*
** File put_two_line.c
*/
void			perspective(t_fdf *fdf, t_coor *point);
void			print_two_line_oy(t_fdf *fdf, t_coor start, t_coor end);
int				skip_point(t_coor point);
void			print_two_line_oz(t_fdf *fdf, t_coor start, t_coor end);
void			print_two_line_ox(t_fdf *fdf, int i, int j);
/*
** File working_string.c
*/
int				count_numbers(char **spl);
void			dell_arr(char **spl);
void			copy_number(int *num, char **spl);
void			dell_map(t_fdf *fdf);
void			working_string(t_fdf *fdf);
/*
** File main.c
*/
void			one_big_string(t_fdf *fdf, int fd);
void			write_map_int(t_fdf *fdf);
void			read_map(t_fdf *fdf, int ac, char **av);
void			calculation_scale(t_fdf *fdf);
int				main(int ac, char **av);
/*
** File projection.c
*/
void			increase_ten(t_fdf *fdf, int *inc, int val);
void			decrease_ten(t_fdf *fdf, int *dec, int val);
void			projection_iso(t_fdf *fdf);
void			projection_parallel(t_fdf *fdf);
void			projection_perpendicular(t_fdf *fdf);
/*
** File press_key.c
*/
void			projection_view(t_fdf *fdf, int key);
void			perspective_size(t_fdf *fdf, int key);
void			len_dz(t_fdf *fdf, int key);
void			press_qw(t_fdf *fdf, int key);
int				press_key(int key, t_fdf *fdf);
#endif
