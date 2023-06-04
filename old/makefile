NAME=cub3d
CFLAGS= #-Wextra -Wall -Werror
LINK= -lmlx -lXext -lX11
INC= inc/cub.h

SRS= src/check_map.c        src/ft_split.c         src/textures_colors.c \
	src/free_elements.c    src/ft_split2.c        src/textures_colors2.c \
	src/ft_itoa.c          src/main.c             src/tools.c  src/creation.c \
	src/get_next_line_utils.c src/get_next_line.c src/intersections.c

OJS= $(SRS:.c=.o)

all: $(NAME)

$(NAME): $(OJS)
	cc -o $(NAME) $(OJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm

%.o:src/%.c $(INC)
	cc -c $(CFLAGS) -I/usr/include -Imlx_linux -O3 $< -o $@

clean:
	rm -rf $(OJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
.PHONY : clean re all fclean
