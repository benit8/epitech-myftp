##
## EPITECH PROJECT, 2018
## myFTP
## File description:
## Makefile
##

SERVER_DIR	=	serv/
CLIENT_DIR	=	client/
LIBRARY_DIR	=	libs/

Libraries	=	cnet	\
			my

LIBS		=	$(addprefix $(LIBRARY_DIR),$(Libraries))

################################################################################

all: libs server client

libs:
	@ for dir in $(LIBS); do make -C $$dir -s; done

server:
	@ make -C $(SERVER_DIR) -s

client:
	@ make -C $(CLIENT_DIR) -s

debug:
	@ for dir in $(LIBS); do make debug -C $$dir -s; done
	@ make debug -C $(SERVER_DIR) -s
	@ make debug -C $(CLIENT_DIR) -s

clean:
	@ for dir in $(LIBS); do make clean -C $$dir -s; done
	@ make clean -C $(SERVER_DIR) -s
	@ make clean -C $(CLIENT_DIR) -s

fclean:
	@ for dir in $(LIBS); do make fclean -C $$dir -s; done
	@ make fclean -C $(SERVER_DIR) -s
	@ make fclean -C $(CLIENT_DIR) -s

re:
	@ for dir in $(LIBS); do make re -C $$dir -s; done
	@ make re -C $(SERVER_DIR) -s
	@ make re -C $(CLIENT_DIR) -s

de:
	@ for dir in $(LIBS); do make de -C $$dir -s; done
	@ make de -C $(SERVER_DIR) -s
	@ make de -C $(CLIENT_DIR) -s

.PHONY: all libs server client debug clean fclean re de