// Server side C/C++ program to demonstrate Socket programming 
#include "server.hpp"

// void Server::setupConnection()
// {
// 	FD_ZERO(&_master);
// 	FD_ZERO(&_readfds);

//     memset(&_address, 0, sizeof _address);
//     _address.sin_family = AF_INET; 
//     _address.sin_addr.s_addr = INADDR_ANY; 
//     _address.sin_port = htons( PORT ); 

//     // Creating socket file descriptor
//     _server_fd = socket(PF_INET, SOCK_STREAM, 0);
//     if (_server_fd < 0) 
//     { 
//         perror("socket failed"); 
//         exit(EXIT_FAILURE); 
//     } 
//     std::cout << "_server_fd = " << _server_fd << std::endl;

//     // Forcefully attaching socket to the port 8080 
//     if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) 
//     { 
//         perror("setsockopt"); 
//         exit(EXIT_FAILURE); 
//     }

//     // Forcefully attaching socket to the port 8080 
//     if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address))<0) 
//     {
//         perror("bind failed"); 
//         exit(EXIT_FAILURE); 
//     }
//     if (listen(_server_fd, 10) < 0) 
//     {
//         perror("listen"); 
//         exit(EXIT_FAILURE); 
//     }
// 	FD_SET(_server_fd, &_master);
// }

// void Server::addConnection()
// {
// 	std::cout << "Accepting" << std::endl;
// 	_addrlen = sizeof(_address); 
// 	_new_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen);
// 	if (_new_socket == -1)
// 	{
// 		perror("accept");
// 	}
// 	else
// 	{
// 		FD_SET(_new_socket, &_master);
// 		if (_new_socket > _fdmax)
// 			_fdmax = _new_socket;
// 		std::cout << "New client connected" << std::endl;
// 	}
// }

// void Server::getRequest(int fd)
// {
// 	_raw_request = "";
// 	do {
// 		_valread = recv(fd, _buffer, BUFLEN - 1, 0);
// 		if (_valread < 0)
// 			perror("recv");
// 		_raw_request.append(_buffer, _valread);
// 		memset(_buffer, 0, BUFLEN);
// 	} while (_valread == BUFLEN - 1);
// #if DEBUG
// 	std::cout << "\nBEGIN REQUEST----------\n\n" << _raw_request << "\n----------END REQUEST\n" << std::endl;
// #endif
// }

// void Server::listening()
// {
// 	RequestParser request;
// 	ResponseHandler response;
// 	while (true) 
//     {
//         _readfds = _master;
// 		std::cout << "hello" << std::endl;
// 		if ((select(_fdmax + 1, &_readfds, NULL, NULL, NULL)) == -1)
//         {
// 			perror("Select failed");
//             exit(EXIT_FAILURE);
//         }
// 		// Loop through exisiting connections looking for data to read
// 		for (int fd = 0; fd <= _fdmax; fd++)
// 		{
// 			if (FD_ISSET(fd, &_readfds)) // returns true if fd is active
//             {
// 				if (fd == _server_fd)
// 					addConnection();
//                 else
//                 {
// 					getRequest(fd);
//                     if (_valread <= 0)
//                     {
//                         if (_valread == 0)
//                             std::cout << "selectserver: socket " << _valread << " hung up" << std::endl;
//                         else
//                             perror("recv");
//                         close(fd);
//                         FD_CLR(fd, &_master);
//                     }
//                     else
//                     {
//                         request.parseRequest(_raw_request);

                        
//                         std::string header_send = response.handleResponse(request.getRequest(), fd);
// 						// std::cout << "\nHEADER BEGIN----------\n" << header_send << "\n----------HEADER END\n" << std::endl;
//                         if ((send(fd , header_send.c_str() , header_send.length() , 0 )) == -1)
//                             perror("send");
//                         close(fd);
//                         FD_CLR(fd, &_master);
//                     }
//                 }
// 			}
// 		}
//     }
// 	close(_server_fd);
// }

int main(int argc, char const *argv[]) 
{
    int					server_fd, fdmax, new_socket, valread; 
    struct sockaddr_in	address;
    fd_set				readfds, master;
    int					opt = 1; 
    int					addrlen; 
    char				buffer[BUFLEN] = {0}; 
	std::string			raw_request;

	std::string			header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: ";
	std::string			header_send;
	std::string			headerfinish = "\r\n\r\n";
	std::string			message;
	char				line[32];
	int					ret = 0;
	std::string			ret_file;

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
		// Loop through exisiting connections looking for data to read
		for (int i = 0; i <= fdmax; i++)
		{
			if (FD_ISSET(i, &readfds)) // returns true if fd is active
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
					raw_request = "";
                    do {
						valread = recv(i, buffer, BUFLEN - 1, 0);
						if (valread < 0)
							perror("recv");
						raw_request.append(buffer, valread);
						memset(buffer, 0, BUFLEN);
					} while (valread == BUFLEN - 1);
#if DEBUG
					std::cout << "\nBEGIN REQUEST----------\n\n" << raw_request << "\n----------END REQUEST\n" << std::endl;
#endif
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
                        request.parseRequest(raw_request);

                        ret_file = ((request.getRequest()).uri).substr(1);
                        int	pagefd = open(ret_file.c_str(), O_RDONLY);
						message = "";
                        while ((ret = read(pagefd, line, 32)) > 0) {
                            message += line;
                            memset(line, 0, 32);
                        }
                        header_send = header + std::to_string(message.length()) + headerfinish + message;
						// std::cout << "\nHEADER BEGIN----------\n" << header_send << "\n----------HEADER END\n" << std::endl;
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
