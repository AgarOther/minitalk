# Compilation
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
LIBFT		=	@make bonus -C ./libft
LIB			=	libft/libft.a

# Names
CLI_NAME	=	client
SRV_NAME	=	server

# Sources & Includes
CLI_SRC		= 	srcs/client.c \
				srcs/client_utils.c
SRV_SRC		=	srcs/server.c
OBJ_FOLDER	=	objs
INCLUDES	=	includes

# Objects
CLI_OBJ		= 	$(OBJ_FOLDER)/client.o \
				$(OBJ_FOLDER)/client_utils.o
SRV_OBJ		= 	$(OBJ_FOLDER)/server.o

# Custom Makefile Flags
MAKEFLAGS	+=	--no-print-directory --silent

# Custom Colors
PURPLE		=	\033[1;35m
LIGHT_GREEN	=	\033[1;32m
RESET		=	\033[0m

# Custom messages
LIB_DONE	=	@echo "🎉$(PURPLE) Libft compiled! 🎉$(RESET)\n"
CLI_DONE	=	@echo "🎉$(PURPLE) Client compiled! 🎉$(RESET)\n"
SRV_DONE	=	@echo "🎉$(PURPLE) Server compiled! 🎉$(RESET)\n"
ALL_CLEAN	=	@echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"
ALL_FCLEAN	=	@echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : check_relink

check_relink:
	@if [ ! -d $(OBJ_FOLDER) ]; then \
		mkdir $(OBJ_FOLDER); \
	fi
	@if [ -f $(SRV_NAME) ] && [ -f $(CLI_NAME) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(SRV_NAME) $(CLI_NAME); \
	fi

$(SRV_NAME): libft $(SRV_OBJ)
	@$(CC) $(CFLAGS) $(SRV_OBJ) $(LIB) -o $(SRV_NAME)
	$(SRV_DONE)

$(CLI_NAME): libft $(CLI_OBJ)
	@$(CC) $(CFLAGS) $(CLI_OBJ) $(LIB) -o $(CLI_NAME)
	$(CLI_DONE)

$(OBJ_FOLDER)/%.o: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(USLEEP)$(SLEEP_TIME) -I $(INCLUDES)

libft : 
	$(LIBFT)
	$(LIB_DONE)

clean :
	@rm -f $(CLI_OBJ) $(SRV_OBJ)
	@cd libft && make clean
	@rm -rf $(OBJ_FOLDER)
	$(ALL_CLEAN)

fclean :
	@rm -f $(CLI_NAME) $(SRV_NAME) $(CLI_OBJ) $(SRV_OBJ)
	@cd libft && make fclean
	@rm -rf $(OBJ_FOLDER)
	$(ALL_FCLEAN)

re : fclean all

.PHONY: all clean fclean re libft client server check_relink
