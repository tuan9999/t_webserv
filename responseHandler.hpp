#ifndef RESPONSE_HANDLER_HPP
# define RESPONSE_HANDLER_HPP

# include "requestParser.hpp"

class ResponseHandler {
	private:
		std::string			_header;
		std::string			_header_send;
		std::string			_headerfinish;
		std::string			_message;
		char				_line[32];
		int					_ret;
		std::string			_ret_file;
	public:
		std::string handleResponse(Request req, int fd);

};

#endif