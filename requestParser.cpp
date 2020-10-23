/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestParser.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tuperera <tuperera@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:17:58 by tuperera      #+#    #+#                 */
/*   Updated: 2020/10/23 13:16:26 by tuperera      ########   odam.nl         */
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
	request_msg = request_msg.substr(pos + 2);
    std::cout << _request.uri;
	
   	// std::cout <<  "request msg == " << request_msg << std::endl;

}