# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tuperera <tuperera@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/26 14:31:20 by tuperera      #+#    #+#                  #
#    Updated: 2020/10/22 12:02:57 by tuperera      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME=webserv

$(NAME):
	g++ server.cpp requestParser.cpp -o $(NAME)

client:
	g++ client.cpp -o client

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) client

re: fclean $(NAME)