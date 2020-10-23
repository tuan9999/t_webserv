/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestParser.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tuperera <tuperera@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/22 11:18:02 by tuperera      #+#    #+#                 */
/*   Updated: 2020/10/22 16:32:36 by tuperera      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP
# include <map>
# include <string>
# include <exception>
# include <iostream>


enum    eHeaderType {
    ACCEPT_CHARSET,
    ACCEPT_LANGUAGE,
    ALLOW,
    AUTHORIZATION,
    CONTENT_LANGUAGE,
    CONTENT_LENGTH,
    CONTENT_LOCATION,
    CONTENT_TYPE,
    DATE,
    HOST,
    LAST_MODIFIED,
    LOCATION,
    REFERER,
    RETRY_AFTER,
    SERVER,
    TRANSFER_ENCODING,
    USER_AGENT,
    WWW_AUTHENTICATE
};

struct  Request {
    std::string							method;
    std::string							uri;
	std::pair<int, int>					version;
	std::map<eHeaderType, std::string>	headers;
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
};

#endif
