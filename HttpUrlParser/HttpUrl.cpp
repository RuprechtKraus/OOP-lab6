#include "HttpUrl.h"
#include "StringLib.h"
#include "UrlParsingError.h"

const std::string HttpUrl::m_urlPattern{
	R"(^(?:(http(?:s)?)?:\/\/)?([a-zA-Z.]*.(?:com|ru|org))(?::(\d+))?(\/[\w\d\?\.\/#,;_=!&\+\*]*)?$)"
};

HttpUrl::HttpUrl(const std::string& url)
{
	ParseUrl(url);
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
	std::string url;
	url += ProtocolToString(m_protocol) + "://" + m_domain;

	if (m_protocol == Protocol::HTTP && m_port != 80 || m_protocol == Protocol::HTTPS && m_port != 443)
	{
		url += ':' + std::to_string(m_port);
	}

	url += m_document;

	return url;
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

void HttpUrl::ParseUrl(const std::string& url)
{
	std::regex rgx(m_urlPattern);
	std::smatch matches;

	if (std::regex_search(url, matches, rgx))
	{
		SetFields(matches);
	}
	else
	{
		throw UrlParsingError("Incorrect url");
	}
}

void HttpUrl::SetFields(const std::smatch& matches)
{
	SetProtocol(matches);
	SetDomain(matches);
	SetPort(matches);
	SetDocument(matches);
}

void HttpUrl::SetProtocol(const std::smatch& matches)
{
	if (matches[1].matched)
	{
		m_protocol = StringToProtocol(matches[1].str());
	}
	else
	{
		m_protocol = Protocol::HTTP;
	}
}

void HttpUrl::SetDomain(const std::smatch& matches)
{
	m_domain = matches[2].str();
}

void HttpUrl::SetPort(const std::smatch& matches)
{
	if (matches[3].matched)
	{
		int port{ std::stoi(matches[3].str()) };

		if (port < 1 || port > 65535)
		{
			throw UrlParsingError("Port is less than 1 or greater than 65535");
		}

		m_port = port;
	}
	else
	{
		m_port = GetDefaultPortForProtocol(m_protocol);
	}
}

void HttpUrl::SetDocument(const std::smatch& matches)
{
	if (matches[4].matched)
	{
		m_document = matches[4].str();
	}
	else
	{
		m_document = "/";
	}
}

int HttpUrl::GetDefaultPortForProtocol(Protocol protocol)
{
	switch (m_protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	default:
		throw std::invalid_argument("Unexpected protocol");
	}
}