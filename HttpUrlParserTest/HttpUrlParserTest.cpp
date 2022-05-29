#include "pch.h"
#include "CppUnitTest.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void VerifyHttpUrl(
	const HttpUrl& httpUrl, 
	const std::string& expectedUrl, 
	const std::string& expectedDomain, 
	const std::string& expectedDocument,
	Protocol expectedProtocol,
	unsigned short expectedPort)
{
	Assert::AreEqual(expectedUrl, httpUrl.GetURL(), 
		L"Actual URL doesn't match expected");
	Assert::AreEqual(expectedDomain, httpUrl.GetDomain(), 
		L"Actual domain doesn't match expected");
	Assert::AreEqual(expectedDocument, httpUrl.GetDocument(), 
		L"Actual document doesn't match expected");
	Assert::AreEqual(ProtocolToString(expectedProtocol), ProtocolToString(httpUrl.GetProtocol()), 
		L"Actual protocol doesn't match expected");
	Assert::AreEqual(std::to_string(expectedPort), std::to_string(httpUrl.GetPort()), 
		L"Actual port doesn't match expected");
}

namespace HttpUrlParserTest
{
	TEST_CLASS(HttpUrlParserTest)
	{
	public:
		
		TEST_METHOD(ConstructHttpUrlFromStringWithoutPortWithDocument)
		{
			std::string url("https://wikipedia.org/wiki/Main_Page");
			HttpUrl httpUrl(url);
			VerifyHttpUrl(httpUrl, url, "wikipedia.org", "/wiki/Main_Page", Protocol::HTTPS, 443);
		}

		TEST_METHOD(ConstructHttpsUrlFromStringWithoutPortWithDocument)
		{
			std::string url("http://www.mysite.com/docs/document1.html?page=30&lang=en#title");
			HttpUrl httpUrl(url);
			VerifyHttpUrl(httpUrl, url, "www.mysite.com", "/docs/document1.html?page=30&lang=en#title",
				Protocol::HTTP, 80);
		}

		TEST_METHOD(ConstructHttpsUrlFromStringWithPortWithDocument)
		{
			std::string url("https://vk.com:8080/im");
			HttpUrl httpUrl(url);
			VerifyHttpUrl(httpUrl, url, "vk.com", "/im",
				Protocol::HTTPS, 8080);
		}

		TEST_METHOD(ConstructHttpUrlFromStringWithPortWithoutDocument)
		{
			std::string url("http://google.com:900");
			HttpUrl httpUrl(url);
			VerifyHttpUrl(httpUrl, "http://google.com:900/", "google.com", "/", Protocol::HTTP, 900);
		}

		TEST_METHOD(ConstructHttpUrlFromStringWithNoProtocol)
		{
			std::string url("google.com/some_document");
			HttpUrl httpUrl(url);
			VerifyHttpUrl(httpUrl, "http://google.com/some_document", "google.com", "/some_document", Protocol::HTTP, 80);
		}

		TEST_METHOD(ConstructHttpUrlFromStringWithInvalidPort)
		{
			std::string url("http://google.com:99999");
			auto createHttpUrl = [&url]() { HttpUrl httpUrl(url); };
			Assert::ExpectException<std::invalid_argument>(createHttpUrl, L"Created HttpUrl with incorrect port");
		}

		TEST_METHOD(ConstructHttpUrlFromStringWithNoDomain)
		{
			std::string url("http:///some_document");
			auto createHttpUrl = [&url]() { HttpUrl httpUrl(url); };
			Assert::ExpectException<UrlParsingError>(createHttpUrl, L"Created HttpUrl with missing domain");
		}

		TEST_METHOD(ConstructHttpUrlProvidingDomainAndDocument)
		{
			HttpUrl httpUrl("www.cplusplus.com", "articles/cpp11/");
			VerifyHttpUrl(httpUrl, "http://www.cplusplus.com/articles/cpp11/", 
				"www.cplusplus.com", "/articles/cpp11/", Protocol::HTTP, 80);
		}

		TEST_METHOD(ConstructHttpUrlProvidingDomainAndEmptyDocument)
		{
			HttpUrl httpUrl("www.cplusplus.com", "");
			VerifyHttpUrl(httpUrl, "http://www.cplusplus.com/",
				"www.cplusplus.com", "/", Protocol::HTTP, 80);
		}

		TEST_METHOD(ConstructHttpUrlProvidingDomainDocumentProtocol)
		{
			HttpUrl httpUrl("www.cplusplus.com", "articles/cpp11/", Protocol::HTTPS);
			VerifyHttpUrl(httpUrl, "https://www.cplusplus.com/articles/cpp11/",
				"www.cplusplus.com", "/articles/cpp11/", Protocol::HTTPS, 443);
		}

		TEST_METHOD(ConstructHttpUrlProvidingDomainDocumentProtocolPort)
		{
			HttpUrl httpUrl("www.cplusplus.com", "articles/cpp11/", Protocol::HTTPS, 5050);
			VerifyHttpUrl(httpUrl, "https://www.cplusplus.com:5050/articles/cpp11/",
				"www.cplusplus.com", "/articles/cpp11/", Protocol::HTTPS, 5050);
		}
	};
}