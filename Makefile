# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slescure <slescure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 17:58:02 by slescure          #+#    #+#              #
#    Updated: 2021/09/16 15:25:40 by slescure         ###   ########.fr        #
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

all: $(CLIENT) $(SERVER)

$(NAME): @ $(MAKE) bonus $(LIBFT_DIR)
	all

$(SERVER): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_SERVER) $(LIBFT) $(INC) -o $(SERVER)
	@echo "$(GREEN)server ready"

$(CLIENT): $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRC_CLIENT) $(LIBFT) $(INC) -o $(CLIENT)
	@echo "$(BLUE)Compilation...$(RESET)"
	@echo "$(GREEN)client ready"

clean:
	@ $(RM) $(SERVER) $(CLIENT)
	@echo "$(RED)Deleting objects...$(RESET)"
	@echo "$(YELLOW)client removed"
	@echo "$(YELLOW)server removed"

fclean: clean
	@ $(RM) $(CLIENT) $(SERVER)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting executables...$(RESET)"

re: clean all

san :
	@(gcc -o $(NAME) -I include $(SRCS) libft/libft.a $(CFLAGS) $(SAN))


.PHONY: all clean fclean re
