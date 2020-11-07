// Server side C/C++ program to demonstrate Socket programming 
#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include "requestParser.hpp"

#define PORT	5000
#define BUFLEN	1024

int main(int argc, char const *argv[]) 
{ 
    int					server_fd, fdmax, new_socket, valread; 
    struct sockaddr_in	address;
    fd_set				readfds, master;
    int					opt = 1; 
    int					addrlen = sizeof(address); 
    char				buffer[BUFLEN] = {0}; 

	std::string			header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: ";
	std::string			header_send;
	std::string			headerfinish = "\r\n\r\n";
	std::string			message;
	char				line[32];
	int					ret = 0;
	std::string			ret_file;
	std::string			request_head;

	RequestParser		request;

	FD_ZERO(&master);
	FD_ZERO(&readfds);

    memset(&address, 0, sizeof address);
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 

    // Creating socket file descriptor
    server_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
    std::cout << "server_fd = " << server_fd << std::endl;

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 10) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
	FD_SET(server_fd, &master);
	fdmax = server_fd;
    while (1) 
    {
        readfds = master;
		if ((select(fdmax + 1, &readfds, NULL, NULL, NULL)) == -1)
        {
			perror("Select failed");
            exit(EXIT_FAILURE);
        }
		for (int i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &readfds))
            {
				if (i == server_fd)
				{
					std::cout << "Accepting" << std::endl;
                    addrlen = sizeof(address); 
					new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                    if (new_socket == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(new_socket, &master);
                        if (new_socket > fdmax)
                            fdmax = new_socket;
						std::cout << "New client connected" << std::endl;
                    }

				}
                else
                {
					std::cout << "Recieving" << std::endl;
					request_head = "";
                    do {
						valread = recv(i, buffer, BUFLEN - 1, 0);
						if (valread < 0)
							perror("recv");
						request_head.append(buffer, valread);
						memset(buffer, 0, BUFLEN);
					} while (valread == BUFLEN - 1);
					
					std::cout << "\n----------\n" << request_head << "\n----------\n" << std::endl;
                    if (valread <= 0)
                    {
                        if (valread == 0)
                            std::cout << "selectserver: socket " << valread << " hung up" << std::endl;
                        else
                            perror("recv");
                        close(i);
                        FD_CLR(i, &master);
                    }
                    else
                    {
                        request.parseRequest(request_head);

                        ret_file = ((request.getRequest()).uri).substr(1);
                        int	pagefd = open(ret_file.c_str(), O_RDONLY);
						message = "";
                        while ((ret = read(pagefd, line, 32)) > 0) {
                            message += line;
                            memset(line, 0, 32);
                        }
                        header_send = header + std::to_string(message.length()) + headerfinish + message;
						std::cout << "\nHEADER BEGIN----------\n" << header_send << "\n----------HEADER END\n" << std::endl;
                        if ((send(i , header_send.c_str() , header_send.length() , 0 )) == -1)
                            perror("send");
                        close(i);
                        FD_CLR(i, &master);
                    }
                }
			}
		}
    }
	close(server_fd);
    return 0; 
}
