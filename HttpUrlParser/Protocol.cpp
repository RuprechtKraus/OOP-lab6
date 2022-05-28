#include "Protocol.h"

std::string ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	default:
		throw std::invalid_argument("Unexpected protocol");
	}
}

Protocol StringToProtocol(const std::string& str)
{
	std::string _str(ToLowerCase(str));

	if (_str == "http")
	{
		return Protocol::HTTP;
	}

	if (_str == "https")
	{
		return Protocol::HTTPS;
	}

	throw std::invalid_argument("Unexpected protocol");
}