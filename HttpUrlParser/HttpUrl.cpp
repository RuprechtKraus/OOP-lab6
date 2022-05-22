#include "HttpUrl.h"
#include "UrlParsingError.h"

// Порт должен быть в диапазоне от 1 до 65535
// Стандартный порт для HTTP - 80
// Стандартный порт для HTTPS - 443
HttpUrl::HttpUrl(const std::string& url)
{
	throw std::logic_error("Method is not implemented");
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document,
	Protocol protocol)
{
	throw std::logic_error("Method is not implemented");
}

HttpUrl::HttpUrl(std::string const& domain, std::string const& document,
	Protocol protocol, unsigned short port)
{
	throw std::logic_error("Method is not implemented");
}

std::string HttpUrl::GetURL() const noexcept
{
	return "";
}

std::string HttpUrl::GetDomain() const noexcept
{
	return m_domain;
}

std::string HttpUrl::GetDocument() const noexcept
{
	return m_document;
}

Protocol HttpUrl::GetProtocol() const noexcept
{
	return m_protocol;
}

unsigned short HttpUrl::GetPort() const noexcept
{
	return m_port;
}

std::string ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "HTTP";
	case Protocol::HTTPS:
		return "HTTPS";
	default:
		throw std::invalid_argument("Unexpected protocol type");
	}
}