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
#define PORT 8080 
int main(int argc, char const *argv[]) 
{ 
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server";

	std::string header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: ";
	std::string headerfinish = "\r\n\r\n";
	std::string	message;
	char line[32];
	int ret = 0;
	char *ret_file = (char *)malloc(sizeof(char) * 100);
	// int		pagefd = open("test.html", O_RDONLY);
	// while (ret = read(pagefd, line, 32) > 0) {
	// 	message += line;
	// 	memset(line, 0, 32);
	// }

	// header = header + std::to_string(message.length()) + headerfinish + message;
	// char len = header.length();
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) 
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
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 30) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) 
    {
		if (new_socket < 0)
		{
			perror("accept"); 
			exit(EXIT_FAILURE); 
		}
		int pid = fork();
		if (pid == -1)
			exit(0);
		if (pid == 0) {
			valread = read( new_socket , buffer, 1024); 
			printf("%s\n",buffer );
			int i = 0;
			int j = 0;
			while(buffer[i] != '/')
				i++;
			i++;
			while(buffer[i] != ' ')
				ret_file[j++] = buffer[i++];
			int	pagefd = open(ret_file, O_RDONLY);
			while (ret = read(pagefd, line, 32) > 0) {
				message += line;
				memset(line, 0, 32);
			}
			header = header + std::to_string(message.length()) + headerfinish + message;
			char len = header.length();
			send(new_socket , header.c_str() , len , 0 ); 
		}
    }
	close(server_fd);
    return 0; 
}