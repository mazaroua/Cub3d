NAME=cub3d
CFLAGS= #-Wextra -Wall -Werror
LINK= -lmlx -framework OpenGL -framework AppKit
INC= inc/cub.h

SRS= src/check_map.c        src/ft_split.c         src/textures_colors.c \
	src/free_elements.c    src/ft_split2.c        src/textures_colors2.c \
	src/ft_itoa.c          src/main.c             src/tools.c  src/creation.c \
	src/get_next_line_utils.c src/get_next_line.c

OJS= check_map.o ft_itoa.o  ft_split2.o textures_colors.o  tools.o free_elements.o  creation.o \
	ft_split.o  main.o  textures_colors2.o get_next_line.o get_next_line_utils.o

all: $(NAME)

$(NAME): $(OJS)
	cc -o $(NAME) $(OJS) $(LINK)

%.o:src/%.c $(INC)
	cc -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
.PHONY : clean re all fclean
