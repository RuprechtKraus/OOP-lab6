#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

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
	std::string m_domain{};
	std::string m_document{};
	Protocol m_protocol{};
	unsigned short m_port{};
};

std::string ProtocolToString(Protocol protocol);