#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <fcntl.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include "requestParser.hpp"
#include "responseHandler.hpp"

#define PORT	5000
#define BUFLEN	1024
#define DEBUG	1

class Server {
	private:
		int					_server_fd,
							_fdmax,
							_new_socket,
							_valread; 
		struct sockaddr_in	_address;
		fd_set				_readfds,
							_master;
		int					_opt; 
		int					_addrlen; 
		char				_buffer[BUFLEN]; 
		std::string			_raw_request;
	public:
		void setupConnection();
		void listening();
		void addConnection();
		void getRequest(int fd);

};

#endif
