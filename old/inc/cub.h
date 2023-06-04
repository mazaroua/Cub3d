#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"

# define PI	 	3.1415926535
# define MEM_ERR "memory allocation error\n"
# define NORTH	'N'
# define SOUTH	'S'
# define EAST	'E'
# define WEST	'W'
# define RIGHT_ROTATION 65363
# define LEFT_ROTATION 65361
# define MOVE_FORWARD 119
# define MOVE_BACKWARD 115
# define MOVE_RIGHT 100
# define MOVE_LEFT 97

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_cub
{
	double	p_x;
	double	p_y;
	float	pdx;
	float	pdy;
	float	pa;
	int		x_map;
	int		y_map;
	int		fd_m;
	void	*m_ptr;
	void	*w_ptr;
	char	*map_1d;
	char	**all;
	char	**map_2d;
	char	***element;
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	char	p_or;
	char	*f_color;
	char	*c_color;
	t_color	*rgb_f;
	t_color	*rgb_c;
	t_data	*data;
	double	next_x;
	double	next_y;
	double	angle;
	double	x_h;
	double	y_h;
	double	x_v;
	double	y_v;
}	t_cub;

void	*ft_malloc(int size);
size_t	map_size(int fd);
char	*ft_strjoin2(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	**ft_split2(char const *s);
int		whitespaces(char c);
void	free_2d(char **str);
void	free_3d(char ***s);
void	release_all(t_cub *cub);
int		size_map(char **str);
void    check_elements(char ***map, t_cub *cub);
int		whitespaces(char c);
void    exit_error(t_cub *cub);
void	check_map(char **map, t_cub *cub, int i);
char	*ft_itoa(int n);
int		ft_atoi(char *str);
bool	isnot_dig(char *str);
void	valid_colors(t_cub *cub, char *s, char c);
char	first_elements(char *str);
void	creation(t_cub *cub);
void	put_player(t_cub *cub);
int		ft_move(int keycode, t_cub *cub);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    horizontal_intersection(t_cub *cub);

#endif