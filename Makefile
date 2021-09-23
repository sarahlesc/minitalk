# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slescure <slescure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 17:58:02 by slescure          #+#    #+#              #
#    Updated: 2021/09/23 18:49:55 by slescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =
CLIENT =	client
SERVER =	server

SRC_CLIENT = client.c
SRC_SERVER = server.c

LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SAN = -g3 -fsanitize=address
RM = rm -rf
INC		=	-I. -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include

ifneq ("$(wildcard $(/libft/libft.a))","")
LIBFT_EXISTS = 1
else
LIBFT_EXISTS = 0
endif

BLACK		:= $(shell tput -Txterm setaf 0)
RED		:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)

all: $(CLIENT) $(SERVER)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_SERVER) $(LIBFT) $(INC) -o $(SERVER)
	@echo "$(GREEN)server ready$(RESET)"

$(CLIENT): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_CLIENT) $(LIBFT) $(INC) -o $(CLIENT)
	@echo "$(BLUE)Compilation...$(RESET)"
	@echo "$(GREEN)client ready$(RESET)"

clean:
	@ $(RM) $(SERVER) $(CLIENT)
	@echo "$(RED)Deleting objects...$(RESET)"
	@echo "$(YELLOW)client removed$(RESET)"
	@echo "$(YELLOW)server removed$(RESET)"

fclean: clean
	@ $(RM) $(CLIENT) $(SERVER)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting executables...$(RESET)"

san :
	@ $(CC) $(CFLAGS) $(SAN) $(SRC_CLIENT) $(LIBFT) $(INC) -o $(CLIENT)
	@ $(CC) $(CFLAGS) $(SAN) $(SRC_SERVER) $(LIBFT) $(INC) -o $(SERVER)

re: fclean all

.PHONY: all clean fclean re
