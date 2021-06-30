# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 21:14:49 by qurobert          #+#    #+#              #
#    Updated: 2021/06/30 14:09:46 by qurobert         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			= philo

FILES			= main.c list.c libft.c error_and_parse.c print.c utils.c

INC_FILES		= philo.h color.h
INC_PATH		= ./includes/
INC				= $(addprefix ${INC_PATH}, ${INC_FILES})

SRC_PATH		= srcs
SRC				= $(addprefix ${SRC_PATH}/, ${FILES})

BIN_PATH		= bin
BIN 			= $(SRC:%.c=$(BIN_PATH)/%.o)

CC				= gcc
RM				= rm -rf
FLAGS			= #-fsanitize=address -g3 -Wall -Wextra  -Werror

all: 			${NAME}

init:
				@$(shell mkdir -p $(BIN_PATH))

$(BIN): $(BIN_PATH)/%.o: %.c ${INC}
				@mkdir -p $(@D)
				@$(CC) $(FLAGS) -I ${INC_PATH} -o $@ -c $<
				@printf "\e[?25l\e[JPHILO : \e[92m$(notdir $<)\e[0m\r"

${NAME}: 		init ${BIN}
				@${CC} ${FLAGS} ${BIN} -o ${NAME} -I ${INC_PATH} -lncurses
				@printf '\033[?25l\033[JPHILO CREATED \033[92m✔ \033[0m\033[?25h\n'

clean:
				@${RM} ${BIN_PATH}
				@printf '\033[?25l\033[JPHILO DELETED \033[92m✔ \033[0m\033[?25h\n'

fclean:
				@${RM} ${BIN_PATH}
				@${RM} ${NAME}
				@printf '\033[?25l\033[JMPHILO DELETED \033[92m✔ \033[0m\033[?25h\n'

re:				fclean all

.PHONY: all clean fclean re bonus init