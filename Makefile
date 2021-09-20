# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slescure <slescure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 17:58:02 by slescure          #+#    #+#              #
#    Updated: 2021/09/20 17:28:23 by slescure         ###   ########.fr        #
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

BLACK		:= $(shell tput -Txterm setaf 0)
RED		:= $(shell tput -Txterm setaf 1)
GREEN		:= $(shell tput -Txterm setaf 2)
YELLOW		:= $(shell tput -Txterm setaf 3)
LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
PURPLE		:= $(shell tput -Txterm setaf 5)
BLUE		:= $(shell tput -Txterm setaf 6)
WHITE		:= $(shell tput -Txterm setaf 7)
RESET		:= $(shell tput -Txterm sgr0)

all:
	$(CLIENT) $(SERVER)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_SERVER) -o $(SERVER)
	@echo "$(GREEN)server ready$(RESET)"

$(CLIENT): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_CLIENT) -o $(CLIENT)
	@echo "$(BLUE)Compilation...$(RESET)"
	@echo "$(GREEN)client ready$(RESET)"

clean:
	@ $(RM) $(SERVER) $(CLIENT)
	@echo "$(RED)Deleting objects...$(RESET)"
	@echo "$(YELLOW)client removed$(RESET)"
	@echo "$(YELLOW)server removed$(RESET)"

fclean: clean
	@ $(RM) $(CLIENT) $(SERVER)
	@echo "$(RED)Deleting executables...$(RESET)"

san :
	@(gcc -o $(NAME) -I include $(SRCS) libft/libft.a $(CFLAGS) $(SAN))

re: fclean all

.PHONY: all clean fclean re
