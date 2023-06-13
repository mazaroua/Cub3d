NAME=cub3d
CFLAGS=# -Wextra -Wall -Werror
#LINK= -lmlx -framework OpenGL -framework AppKit -lm
LINK = -lmlx -lXext -lX11 -lm
INC= inc/cub.h  inc/objects.h inc/get_next_line.h

SRS= src/castrays.c       src/ft_split.c             src/player_mov.c \
	src/check_map.c      src/get_next_line.c        src/surfaces.c \
	src/convert.c        src/get_next_line_utils.c  src/textures_colors2.c \
	src/creation.c       src/init.c                 src/textures_colors.c \
	src/free_elements.c  src/intersections.c        src/tools.c \
	src/ft_itoa.c        src/main.c \
	src/ft_split2.c      src/new_texture.c

OJS= $(SRS:.c=.o)

all: $(NAME)

$(NAME): $(OJS)
	cc $(CFLAGS) -o $(NAME) $(OJS) $(LINK)

%.o:src/%.c $(INC)
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
.PHONY : clean re all fclean
