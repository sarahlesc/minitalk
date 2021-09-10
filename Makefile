# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slescure <slescure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 17:58:02 by slescure          #+#    #+#              #
#    Updated: 2021/09/10 18:16:16 by slescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =
CLIENT =	client
SERVER =	server

SRC_CLIENT = client.c
SRC_SERVER = server.c


CC = gcc
CFLAGS = -Wall -Wextra -Werror
SAN = -g3 -fsanitize=address
RM = rm -rf

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

$(SERVER):
	@ $(CC) $(CFLAGS) $(SRC_SERVER) -o $(SERVER)
	@echo "$(GREEN)server ready"

$(CLIENT):
	@ $(CC) $(CFLAGS) $(SRC_CLIENT) -o $(CLIENT)
	@echo "$(BLUE)Compilation...$(RESET)"
	@echo "$(GREEN)client ready"

clean:
	@ $(RM) $(SERVER) $(CLIENT)
	@echo "$(RED)Deleting objects...$(RESET)"
	@echo "$(YELLOW)client removed"
	@echo "$(YELLOW)server removed"

fclean: clean
	@ $(RM) $(CLIENT) $(SERVER)
	@echo "$(RED)Deleting executables...$(RESET)"

re: fclean all

.PHONY: all clean fclean re
