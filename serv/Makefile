##
## EPITECH PROJECT, 2018
## myftp
## File description:
## Makefile
##

PROJECT	=	Server
NAME	=	../server

SRC_DIR	=	src/

SOURCES	=	main.c			\
		client.c		\
		data_channel.c		\
		commands.c		\
		input.c			\
		response.c		\
		status.c		\
		commands/appe.c		\
		commands/cdup.c		\
		commands/cwd.c		\
		commands/dele.c		\
		commands/help.c		\
		commands/list.c		\
		commands/mkd.c		\
		commands/mode.c		\
		commands/noop.c		\
		commands/pass.c		\
		commands/pasv.c		\
		commands/port.c		\
		commands/pwd.c		\
		commands/quit.c		\
		commands/retr.c		\
		commands/rmd.c		\
		commands/rnfr.c		\
		commands/rnto.c		\
		commands/stor.c		\
		commands/stru.c		\
		commands/syst.c		\
		commands/type.c		\
		commands/unknown.c	\
		commands/user.c		\

SRCS	=	$(addprefix $(SRC_DIR),$(SOURCES))
OBJS	=	$(SRCS:.c=.o)

################################################################################

CFLAGS	+=	-W -Wall -Wextra
CFLAGS	+=	-Iinclude/
CFLAGS	+=	-I../libs/cnet/include/
CFLAGS	+=	-I../libs/my/includes/

LDFLAGS	+=	-L../libs/
LDFLAGS	+=	-lcnet
LDFLAGS	+=	-lmy

################################################################################

SHELL	=	/bin/bash
PRINT	=	printf "$(PROJECT):\t" ; printf
RM	=	rm -f
CC	=	gcc

RESET	=	\033[0m
RED	=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
BLUE	=	\033[0;34m
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;36m

################################################################################

all: $(NAME)

debug: CFLAGS += -g3 -D DEBUG
debug: $(NAME)

$(NAME): prebuild $(OBJS)
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Building $(NAME)"
	@ $(CC) -o $(NAME) $(OBJS) $(LDFLAGS) && \
	  (printf "$(GREEN)Done$(RESET)\n" ; exit 0) || \
	  (printf "$(RED)Fail$(RESET)\n" ; exit 1)

prebuild:
	@ $(PRINT) "$(YELLOW)%b$(RESET)\n" "Compiling source files"

clean:
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting object files"
	@ $(RM) $(OBJS)
	@ printf "$(GREEN)Done$(RESET)\n"

fclean: clean
	@ $(PRINT) "$(YELLOW)%-40b$(RESET)" "Deleting $(NAME)"
	@ $(RM) $(NAME)
	@ printf "$(GREEN)Done$(RESET)\n"

re: fclean all
de: fclean debug

.c.o:
	@ $(CC) -c $< -o $@ $(CFLAGS) && \
	  ($(PRINT) "  $(GREEN)[OK]$(CYAN)  %b$(RESET)\n" $<) || \
	  ($(PRINT) "  $(RED)[XX]$(CYAN)  %b$(RESET)\n" $< ; exit 1)

.PHONY: all $(NAME) prebuild clean fclean re .c.o