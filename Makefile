LEM_IN = lem-in

GNLDIR = get_next_line

SRCDIR = src

SRC_LEM_IN =    depth_algorithm/choose_path_group.c \
                breadth_algorithm/find_path_groups.c \
                breadth_algorithm/calculate.c \
                breadth_algorithm/find_path_groups_helpers.c \
                breadth_algorithm/reset.c \
                depth_algorithm/get_all_paths.c \
                depth_algorithm/find.c \
                list/list.c \
                list/create.c \
                list/add.c \
                list/add_room.c \
                parse/parse.c \
                parse/parse_rooms.c \
                free/free_1.c \
                free/free_2.c \
                display.c \
                err_atoi.c \
                errors.c \
                generate_steps.c \
                create_steps.c \
                graph.c \
                main.c \
                room.c \
                debug_display.c \
                get_next_write.c

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
