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
# include "objects.h"

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
void	my_mlx_pixel_put(t_cub *c, int x, int y, int color);
void    init_values(t_cub *cub);
int 	ft_move(int keycode, t_cub *cub);
void 	draw_mini_map(t_cub *cub);
bool	check_wall(t_cub *cub);
void    intersections(double rayangle, t_cub *cub);
void	cast_all_rays(t_cub *cub);
void    DDA(t_cub *cub);
void	render_walls(double rayangle, t_cub *cub, int i);
double  cal_distance(double x1, double y1, double x2, double y2);
void	put_surfaces(t_cub *cub);
double	set_angle(double angle);
t_tx   *new_texture(t_cub *cub, char *file);
//void    load_textures(t_cub *data);
void	set_textures(t_cub *cub);
#endif