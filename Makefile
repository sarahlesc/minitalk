# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slescure <slescure@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/09 17:58:02 by slescure          #+#    #+#              #
#    Updated: 2021/09/09 18:00:12 by slescure         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SRCS = client.c		\
	server.c		\


OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror
