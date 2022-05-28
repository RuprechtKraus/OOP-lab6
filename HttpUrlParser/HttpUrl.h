#pragma once
#include "Protocol.h"
#include <regex>
#include <string>

class HttpUrl
{
public:
	HttpUrl() = delete;

	explicit HttpUrl(const std::string& url);

	HttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol = Protocol::HTTP);

	HttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol, unsigned short port);

	std::string GetURL() const noexcept;
	std::string GetDomain() const noexcept;
	std::string GetDocument() const noexcept;
	Protocol GetProtocol() const noexcept;
	unsigned short GetPort() const noexcept;

private:
	void ParseUrl(const std::string& url);
	void SetFields(const std::smatch& matches);
	void SetProtocol(const std::smatch& matches);
	void SetDomain(const std::smatch& matches);
	void SetPort(const std::smatch& matches);
	void SetDocument(const std::smatch& matches);
	int GetDefaultPortForProtocol(Protocol protocol);

	std::string m_domain{};
	std::string m_document{};
	Protocol m_protocol{};
	unsigned short m_port{};
	static const std::string m_urlPattern;
};