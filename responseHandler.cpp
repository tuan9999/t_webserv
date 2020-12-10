#include "responseHandler.hpp"
#include "server.hpp"

std::string ResponseHandler::handleResponse(Request req, int fd)
{
	_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-length: ";
	_headerfinish = "\r\n\r\n";
	_ret = 0;

	_ret_file = (req.uri).substr(1);
	int	pagefd = open(_ret_file.c_str(), O_RDONLY);
	_message = "";
	while ((_ret = read(pagefd, _line, 32)) > 0) {
		_message += _line;
		memset(_line, 0, 32);
	}
	_header_send = _header + std::to_string(_message.length()) + _headerfinish + _message;
	// std::cout << "\nHEADER BEGIN----------\n" << header_send << "\n----------HEADER END\n" << std::endl;
	if ((send(fd , _header_send.c_str() , _header_send.length() , 0 )) == -1)
		perror("send");
}