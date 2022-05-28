#include "HttpUrl.h"
#include "StringLib.h"
#include "UrlParsingError.h"

const std::string HttpUrl::m_urlPattern{
	R"(^(?:(http(?:s)?)?:\/\/)?([a-zA-Z.]*.(?:com|ru|org))(?::(\d+))?(\/[\w\d\?\.\/#,;_=!&\+\*]*)?$)"
};

const std::string HttpUrl::m_domainPattern{
	R"([a-zA-Z.]*.(?:com|ru|org))"
};

HttpUrl::HttpUrl(const std::string& url)
{
	ParseUrl(url);
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document,
	Protocol protocol)
	: HttpUrl(domain, document, protocol, GetDefaultPortForProtocol(protocol))
{
}

HttpUrl::HttpUrl(const std::string& domain, const std::string& document,
	Protocol protocol, unsigned short port)
{
	std::regex rgx(m_domainPattern);

	if (std::regex_match(domain, rgx))
	{
		std::string tmpDomain(domain);
		std::string tmpDocument(AddFrontSlashToDocument(document));

		if (!IsPortCorrect(port))
		{
			throw std::invalid_argument("Port is less than 1 or greater than 65535");
		}

		std::swap(m_domain, tmpDomain);
		std::swap(m_document, tmpDocument);
		m_protocol = protocol;
		m_port = port;
	}
	else
	{
		throw std::invalid_argument("Incorrect domain");
	}
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
	Protocol protocol{ GetProtocolFromMatches(matches) };
	HttpUrl tmp(GetDomainFromMatches(matches), GetDocumentFromMatches(matches), 
		protocol, GetPortFromMatches(matches, protocol));
	std::swap(*this, tmp);
}

Protocol HttpUrl::GetProtocolFromMatches(const std::smatch& matches)
{
	if (matches[1].matched)
	{
		return StringToProtocol(matches[1].str());
	}
	else
	{
		return Protocol::HTTP;
	}
}

std::string HttpUrl::GetDomainFromMatches(const std::smatch& matches)
{
	return matches[2].str();
}

unsigned short HttpUrl::GetPortFromMatches(const std::smatch& matches, Protocol protocol)
{
	if (matches[3].matched)
	{
		int port{ std::stoi(matches[3].str()) };

		if (!IsPortCorrect(port))
		{
			throw std::invalid_argument("Port is less than 1 or greater than 65535");
		}

		return port;
	}
	else
	{
		return GetDefaultPortForProtocol(protocol);
	}
}

std::string HttpUrl::GetDocumentFromMatches(const std::smatch& matches)
{
	if (matches[4].matched)
	{
		return matches[4].str();
	}
	else
	{
		return "/";
	}
}

unsigned short HttpUrl::GetDefaultPortForProtocol(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return 80;
	case Protocol::HTTPS:
		return 443;
	default:
		throw std::invalid_argument("Unexpected protocol");
	}
}

bool HttpUrl::IsPortCorrect(int port) noexcept
{
	return port >= 1 && port <= 65535;
}

std::string HttpUrl::AddFrontSlashToDocument(const std::string& document)
{
	if (document.empty())
	{
		return "/";
	}
	else if (document[0] != '/')
	{
		return "/" + document;
	}

	return document;
}