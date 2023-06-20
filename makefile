NAME=cub3d
CFLAGS= -Wextra -Wall -Werror
LINK= -lmlx -framework OpenGL -framework AppKit -lm
INC= inc/cub.h  inc/objects.h inc/get_next_line.h
MLX = minilibx/libmlx.a
GNL= gnl/get_next_line.c  gnl/get_next_line_utils.c
#------------------------files---------------------------------------------
SRS=mandatory/castrays.c            mandatory/init.c \
	mandatory/parsing4.c           mandatory/intersections.c \
	mandatory/convert.c             mandatory/main.c \
	mandatory/creation.c            mandatory/new_texture.c \
	mandatory/free_elements.c       mandatory/player_mov.c \
	mandatory/ft_itoa.c             mandatory/surfaces.c \
	mandatory/ft_split.c            mandatory/parsing2.c \
	mandatory/ft_split2.c           mandatory/parsing3.c \
    mandatory/tools.c 				mandatory/parsing1.c $(GNL)
	
OJS= $(SRS:.c=.o)
#----------------------bonus part----------------------------------------
BSRS=bonus/castrays.c            bonus/init.c \
	bonus/check_map.c           bonus/intersections.c \
	bonus/convert.c             bonus/main.c \
	bonus/creation.c            bonus/new_texture.c \
	bonus/free_elements.c       bonus/player_mov.c \
	bonus/ft_itoa.c             bonus/surfaces.c \
	bonus/ft_split.c            bonus/textures_colors.c \
	bonus/ft_split2.c          	bonus/zoomed_map.c \
	bonus/tools.c 				bonus/textures_colors2.c \
	$(GNL)

BOJS= $(BSRS:.c=.o)
#-------------------------rules-------------------------------------------
all: $(NAME)

$(NAME): $(MLX) $(OJS)
	cc $(CFLAGS) -o $(NAME) $(MLX) $(OJS) $(LINK)

%.o:mandatory/%.c $(INC)
	cc -c $(CFLAGS) $< -o $@

bonus: $(MLX) $(BOJS)
	cc $(CFLAGS) -o $(NAME) $(MLX) $(BOJS) $(LINK)

%.o:bonus/%.c $(INC)
	cc -c $(CFLAG)  $< -o $@

$(MLX):
	@make -C ./minilibx

clean:
	@rm -rf $(OJS) $(BOJS)

fclean: clean
	@make clean -C ./minilibx
	@rm -rf $(NAME)

re : fclean all
.PHONY : clean re all fclean bonus