# Compilation

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

LIBFT		= @cd libft && make

LIB			= libft/libft.a

USLEEP		= -D SLEEP_TIME=

# Define usleep time (wait time between signals).
# Higher value means more execution time but more accurate.
# Lower value means less accurate but faster.
# /!\ Values that are too small WON'T work!
# [Default: 100]

SLEEP_TIME	= 1000

# Names

CLI_NAME	= client

SRV_NAME	= server

# Sources & Includes

CLI_SRC		= srcs/client.c

SRV_SRC		= srcs/server.c

OBJ_FOLDER	= objs/

INCLUDES	= includes

# Objects

CLI_OBJ		= $(OBJ_FOLDER)client.o

SRV_OBJ		= $(OBJ_FOLDER)server.o

# Custom Makefile Flags

MAKEFLAGS	+= --no-print-directory --silent

# Custom Colors

PURPLE		= \033[1;35m

LIGHT_GREEN	= \033[1;32m

RESET		= \033[0m

# Custom messages

LIB_DONE	= @echo "🎉$(PURPLE) Libft compiled! 🎉$(RESET)\n"

CLI_DONE	= @echo "🎉$(PURPLE) Client compiled! 🎉$(RESET)\n"

SRV_DONE	= @echo "🎉$(PURPLE) Server compiled! 🎉$(RESET)\n"

ALL_CLEAN	= @echo "🧹$(LIGHT_GREEN) Project's objects cleaned! 🧹$(RESET)\n"

ALL_FCLEAN	= @echo "🧹$(LIGHT_GREEN) Project's objects & Executables cleaned! 🧹$(RESET)\n"

# Rules

all : check_relink

check_relink:
	@if [ -f $(SRV_NAME) ] && [ -f $(CLI_NAME) ]; then \
		echo '✅$(LIGHT_GREEN) Nothing to be done for "all"! ✅$(RESET)\n'; \
	else \
		$(MAKE) $(SRV_NAME) $(CLI_NAME); \
	fi

$(SRV_NAME)			: $(SRV_OBJ) libft
	@$(CC) $(CFLAGS) $(SRV_OBJ) $(LIB) -o $(SRV_NAME)
	$(SRV_DONE)

$(CLI_NAME)			: $(CLI_OBJ) libft
	@$(CC) $(CFLAGS) $(CLI_OBJ) $(LIB) -o $(CLI_NAME)
	$(CLI_DONE)

$(OBJ_FOLDER)%.o	: srcs/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(USLEEP)$(SLEEP_TIME) -I $(INCLUDES)

libft : 
	$(LIBFT)
	$(LIB_DONE)

clean :
	@rm -f $(CLI_OBJ) $(SRV_OBJ)
	@cd libft && make clean
	$(ALL_CLEAN)

fclean :
	@rm -f $(CLI_NAME) $(SRV_NAME) $(CLI_OBJ) $(SRV_OBJ)
	@cd libft && make fclean
	$(ALL_FCLEAN)

re : fclean all

.PHONY: all clean fclean re libft client server check_relink
