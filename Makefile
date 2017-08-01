LEM_IN = lem-in

GNLDIR = get_next_line

SRCDIR = src

SRC_LEM_IN =    display.c \
                err_atoi.c \
                errors.c \
                find_path_groups.c \
                free.c \
                get_all_paths.c \
                graph.c \
                list.c \
                main.c \
                parse.c \
                room.c

GNL = get_next_line.c

OBJ_LEM_IN = $(addprefix $(SRCDIR)/, $(SRC_LEM_IN:.c=.o))

OBJ_GNL = $(addprefix $(GNLDIR)/, $(GNL:.c=.o))

LIB_PATH = $(GNLDIR)/libft

all: $(OBJ_LEM_IN) $(OBJ_GNL)
	make -C $(LIB_PATH)
	gcc -g -Wall -Wextra -Werror -o $(LEM_IN) $(OBJ_LEM_IN) $(OBJ_GNL) $(LIB_PATH)/libft.a

%.o: %.c
	gcc -g -c -Wall -Wextra -Werror -o $@ $<

clean:
	rm -f $(OBJ_LEM_IN)
	rm -f $(OBJ_GNL)
	make clean -C $(LIB_PATH)

fclean:
	rm -f $(LEM_IN)
	rm -f $(OBJ_LEM_IN)
	rm -f $(OBJ_GNL)
	make fclean -C $(LIB_PATH)

re: fclean all
