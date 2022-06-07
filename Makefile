# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 20:06:31 by hyko              #+#    #+#              #
#    Updated: 2022/06/07 19:32:49 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
SERVER = server
CLIENT = client

CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -rf

SERVER_SRCS = server.c
CLIENT_SRCS = client.c

SERVER_OBJS = server.o
CLIENT_OBJS = client.o

SERVER_SRCS_BONUS = server_bonus.c
CLIENT_SRCS_BONUS = client_bonus.c

SERVER_OBJS_BONUS = server_bonus.o
CLIENT_OBJS_BONUS = client_bonus.o

ifdef MAKE_BONUS
	S_OBJ = $(SERVER_OBJS_BONUS)
	C_OBJ = $(CLIENT_OBJS_BONUS)
else
	S_OBJ = $(SERVER_OBJS)
	C_OBJ = $(CLIENT_OBJS)
endif

all : $(NAME)

$(NAME) : $(SERVER) $(CLIENT)

bonus :
	$(MAKE) MAKE_BONUS=1 all

$(SERVER) : $(S_OBJ)
	$(CC) $(CFLAG) -o $@ $^

$(CLIENT) : $(C_OBJ)
	$(CC) $(CFLAG) -o $@ $^

clean :
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_OBJS_BONUS) $(CLIENT_OBJS_BONUS)

fclean : clean
	$(RM) $(SERVER) $(CLIENT)

re : fclean all

.PHONY : all clean fclean re bonus