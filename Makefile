# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tuperera <tuperera@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/26 14:31:20 by tuperera      #+#    #+#                  #
#    Updated: 2020/12/10 19:16:12 by tuperera      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=webserv

FLAGS= -Wall -Werror -Wextra
FLAGS_DEBUG= -Wall -Wextra -g

$(NAME):
	g++ server.cpp requestParser.cpp responseHandler.cpp -o $(NAME)

client:
	g++ client.cpp -o client

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) client

re: fclean $(NAME)