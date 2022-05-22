#pragma once
#include <stdexcept>

class UrlParsingError : public std::invalid_argument
{
public:
	explicit UrlParsingError(const std::string& message)
		: invalid_argument(message){};

	explicit UrlParsingError(const char* message)
		: invalid_argument(message){};
};