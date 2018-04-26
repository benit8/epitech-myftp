##
## EPITECH PROJECT, 2018
## myftp
## File description:
## Makefile
##

PROJECT	=	Client
NAME	=	../myftp

SRC_DIR	=	src/

SOURCES	=	main.c			\
		commands.c		\
		connection.c		\
		prompt.c		\
		response.c		\
		response_utils.c	\
		commands/append.c	\
		commands/ascii.c	\
		commands/binary.c	\
		commands/cd.c		\
		commands/cdup.c		\
		commands/debug.c	\
		commands/delete.c	\
		commands/disconnect.c	\
		commands/exit.c		\
		commands/help.c		\
		commands/lcd.c		\
		commands/list.c		\
		commands/mkdir.c	\
		commands/noop.c		\
		commands/open.c		\
		commands/passive.c	\
		commands/pwd.c		\
		commands/quote.c	\
		commands/recv.c		\
		commands/rename.c	\
		commands/rmdir.c	\
		commands/send.c		\
		commands/user.c

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

debug: CFLAGS += -g3
debug: CFLAGS += -DDEBUG
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