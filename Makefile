# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 23:31:10 by inicole-          #+#    #+#              #
#    Updated: 2023/08/17 04:53:23 by inicole-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror
FLAGS	= -pthread

INCD_	= philo.h
INCD_DIR	= ./inc

SRCS	= \
			args.c \
			handler.c \
			main.c \
			monitor.c \
			philo.c \
			routine_utils.c \
			routine.c \
			sleep.c \
			utils.c
SRCS_DIR	= ./src

OBJS_DIR	= ./obj
OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

SRCS_PATH	= $(addprefix $(SRCS_DIR)/, $(SRCS))

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I $(INCD_DIR) -c $< -o $@

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(FLAGS) -I $(INCD_DIR) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) debug

re: fclean all

debug: $(OBJS)
	$(CC) -g $(CFLAGS) $(FLAGS) -I $(INCD_DIR) $(SRCS_PATH) -o $@

.PHONY: all clean fclean re