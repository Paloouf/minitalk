# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/16 14:22:58 by ltressen          #+#    #+#              #
#    Updated: 2023/03/17 14:06:32 by ltressen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

NAME = minitalk.a

EXEC_CLIENT = client
EXEC_SERVER = server
SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = ${SRC_CLIENT:.c=.o} 
OBJ_SERVER = ${SRC_SERVER:.c=.o}
	
all: $(NAME)  clean

$(NAME):
	make -C libft/
	mv libft/libft.a ${NAME}
	gcc -c ${FLAGS} ${SRC_CLIENT} ${SRC_SERVER}
	ar rc ${NAME} ${OBJ_CLIENT} ${OBJ_SERVER}
	gcc ${FLAGS} ${SRC_CLIENT} ${NAME} -o ${EXEC_CLIENT}
	gcc ${FLAGS} ${SRC_SERVER} ${NAME} -o ${EXEC_SERVER}
	
clean:
	make clean -C libft/
	rm -f ${OBJ_CLIENT} ${OBJ_SERVER}

fclean:
	make clean -C libft/
	rm -f ${OBJ_CLIENT} ${OBJ_SERVER}
	rm -f ${NAME} ${EXEC_CLIENT} ${EXEC_SERVER}

re: fclean all
