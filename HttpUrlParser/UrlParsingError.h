#pragma once
#include <stdexcept>

class UrlParsingError : public std::invalid_argument
{
public:
	using MyBase = invalid_argument;

	explicit UrlParsingError(const std::string& message)
		: MyBase(message){};

	explicit UrlParsingError(const char* message)
		: MyBase(message){};
};