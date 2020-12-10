/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestParser.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tuperera <tuperera@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:17:58 by tuperera      #+#    #+#                 */
/*   Updated: 2020/12/10 18:13:29 by tuperera      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "requestParser.hpp"

RequestParser::RequestParser()
{
    
}

RequestParser::~RequestParser()
{
    
}

RequestParser::RequestParser(const RequestParser& src)
{
    
}

RequestParser&  RequestParser::operator=(const RequestParser& rhs)
{
    
}

Request         RequestParser::getRequest() const
{
    return _request;
}

size_t			RequestParser::getMethod(std::string request_msg)
{
    size_t pos = 0;

    pos = request_msg.find(' ');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: No whitespace found.");
    _request.method = request_msg.substr(0, pos);
    return (pos);
}

size_t			RequestParser::getUri(std::string request_msg)
{
    size_t pos = 0;

    pos = request_msg.find(' ');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: No whitespace found.");
    _request.uri = request_msg.substr(0, pos);
    return (pos);
}

size_t			RequestParser::getHttpVersion(std::string request_msg)
{
    size_t pos = 0;
	size_t pos_2 = 0;

    pos = request_msg.find('/');
	if (pos == std::string::npos)
		throw std::runtime_error("Error: No / found in http version.");
    pos_2 = request_msg.find('.');
	if (pos_2 == std::string::npos)
		throw std::runtime_error("Error: No . found in http version.");

    _request.version.first = atoi((request_msg.substr(pos + 1, pos_2)).c_str());

    pos = pos_2;
	request_msg = request_msg.substr(pos + 1);
	
    pos_2 = request_msg.find("\r\n");
	if (pos_2 == std::string::npos)
		throw std::runtime_error("Error: No CRLF found in http version.");
	
    _request.version.second = atoi((request_msg.substr(0, pos_2)).c_str());
    return (pos_2);
}

size_t			RequestParser::getHeaders(std::string request_msg)
{
	std::string header;
	std::string header_key;
	std::string header_val;
	std::size_t pos;
	int i = 0;
	std::cout << request_msg << std::endl;
	std::cout << "START" << std::endl;
	while (request_msg.size() > 0)
	{
		i++;
		pos = request_msg.find("\r\n");
		if (pos != request_msg.find("\r\n\r\n"))
		{
			header = request_msg.substr(0, pos + 2);
			std::cout << "HEADER = " << header << std::endl;
			header_key = header.substr(0, header.find(":"));
			std::cout << "header_key = " << header_key << std::endl;
			header_val = header.substr(header.find(":") + 2, header.find("\r\n"));
			std::cout << "header_val = " << header_val << std::endl;
			_request.headers.insert(std::pair<std::string, std::string>(header_key, header_val));
			request_msg = request_msg.substr(pos+2);
		}
		else
			break ;
	}
	return pos;
}

void			RequestParser::parseRequest(std::string request_msg)
{
	size_t		pos;
    if (request_msg[0] == ' ')
        throw std::runtime_error("Error: Invalid whitespace.");
    pos = getMethod(request_msg);
	request_msg = request_msg.substr(pos + 1);
    pos = getUri(request_msg);
	request_msg = request_msg.substr(pos + 1);
    pos = getHttpVersion(request_msg);
	request_msg = request_msg.substr(pos + 9);
	pos = getHeaders(request_msg);
#if DEBUG & DEBUG_PARSE
	std::map<std::string, std::string>::iterator it;
	std::cout << "map stuff" << std::endl;
	for (it = _request.headers.begin(); it != _request.headers.end(); it++){
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << _request.headers["Connection"];
    std::cout << _request.uri << " " << _request.method << " " << _request.version.first << " " << _request.version.second;
#endif

}