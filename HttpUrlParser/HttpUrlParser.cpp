#include "HttpUrl.h"
#include <iostream>

int main()
{
	std::cout << "Enter url: ";
	std::string url;
	std::cin >> url;

	while (!std::cin.eof())
	{
		try
		{
			HttpUrl httpUrl(url);
			std::cout << "Protocol: " << ProtocolToString(httpUrl.GetProtocol())
					  << "\nDomain: " << httpUrl.GetDomain()
					  << "\nPort: " << httpUrl.GetPort()
					  << "\nDocument: " << httpUrl.GetDocument()
					  << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		std::cout << "\nEnter url: ";
		std::cin >> url;
	}
}