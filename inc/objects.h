#ifndef OBJECTS_H
# define OBJECTS_H

# define WIN_WITH	800
# define WIN_HEIGTH 600
# define NUM_RAYS	WIN_WITH
# define S_SIZE		32
# define FOV_AGL  (60 * (M_PI / 180))
# define MEM_ERR "memory allocation error\n"
# define IMG_ERR "Invalid file path\n"
# define NORTH	'N'
# define SOUTH	'S'
# define EAST	'E'
# define WEST	'W'
# define DOR	'D'
# define RIGHT_ROTATION 65363
# define LEFT_ROTATION 65361
# define MOVE_FORWARD 122
# define MOVE_BACKWARD 115
# define MOVE_RIGHT 100
# define MOVE_LEFT 113
# define ESC 65307
# define SCALE_SIZE 0.3
# define OPEN_DOOR 32
//z  122
//q  113
//s  115
//d  100
//esc  65307
//left   65361
//right   65363
//mac-------------------
// w  13
// a  0
// s  1
// d  2
// esc   53
// left   123
// right   124
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct	s_ray
{
	int		dx;
	int 	dy;
	double	nxtx;
	double	nxty;
	int		steps;
	float	Xinc;
	float	Yinc;
	float 	X;
	float	Y;
}	t_ray;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_data;

typedef struct	s_tx
{
	void			*ptr;
	unsigned int	*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	char			*type;
	int				sprite_x;
	int				sprite_yY;
}	t_tx;

typedef struct s_cub
{
	double	p_x;
	double	p_y;
	float	pdx;
	float	pdy;
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
	int		num_rays;
	int		win_width;
	int		win_height;
	double	next_x;
	double	next_y;
	double	x_h;
	double	y_h;
	double	x_v;
	double	y_v;
	double	angle;
	t_tx	*north_txt;
	t_tx	*south_txt;
	t_tx	*west_txt;
	t_tx	*east_txt;
	t_tx	*door_txt;
	bool	hori_line;
	bool	vert_line;
	bool	door;
	bool	close_door;
	int		door_x;
	int		door_y;
	double	d_p_dist;
	double	p_minix;
	double	p_miniy;
	int		door_index;
	int		door_row;
	//double	nxt_minix;
	//double	nxt_miniy;
	double	x_offset;
}	t_cub;

#endif