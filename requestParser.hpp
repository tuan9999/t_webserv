/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestParser.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tuperera <tuperera@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:18:02 by tuperera      #+#    #+#                 */
/*   Updated: 2020/12/10 18:12:53 by tuperera      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP
# include <map>
# include <string>
# include <exception>
# include <iostream>

#define DEBUG_PARSE 0

struct  Request {
    std::string							method;
    std::string							uri;
	std::pair<int, int>					version;
	std::map<std::string, std::string>	headers;
};

class   RequestParser {
    private:
		Request	_request;

    public:
        RequestParser();
        ~RequestParser();
        RequestParser(const RequestParser& src);

        RequestParser&  operator=(const RequestParser& rhs);

        Request         getRequest() const;

		void			parseRequest(std::string request_msg);
		size_t			getMethod(std::string request_msg);
		size_t			getUri(std::string request_msg);
		size_t			getHttpVersion(std::string request_msg);
		size_t			getHeaders(std::string request_msg);
};

#endif
