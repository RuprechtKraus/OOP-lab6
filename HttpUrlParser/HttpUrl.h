#pragma once
#include "Protocol.h"
#include <regex>
#include <string>

class HttpUrl
{
public:
	explicit HttpUrl(const std::string& url);

	HttpUrl(const std::string& domain, const std::string& document,
		Protocol protocol = Protocol::HTTP);

	HttpUrl(const std::string& domain, const std::string& document,
		Protocol protocol, unsigned short port);

	std::string GetURL() const noexcept;
	std::string GetDomain() const noexcept;
	std::string GetDocument() const noexcept;
	Protocol GetProtocol() const noexcept;
	unsigned short GetPort() const noexcept;

private:
	void ParseUrl(const std::string& url);
	void SetFields(const std::smatch& matches);
	Protocol GetProtocolFromMatches(const std::smatch& matches);
	std::string GetDomainFromMatches(const std::smatch& matches);
	std::string GetDocumentFromMatches(const std::smatch& matches);
	unsigned short GetPortFromMatches(const std::smatch& matches, 
		[[maybe_unused]] Protocol protocol = Protocol::HTTP);

	static unsigned short GetDefaultPortForProtocol(Protocol protocol);
	static bool IsPortCorrect(int port) noexcept;
	std::string AddFrontSlashToDocument(const std::string& document);

	std::string m_domain{};
	std::string m_document{};
	Protocol m_protocol{};
	unsigned short m_port{};

	static const std::string m_urlPattern;
	static const std::string m_domainPattern;
};