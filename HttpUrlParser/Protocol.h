#pragma once
#include "StringLib.h"
#include <stdexcept>

enum class Protocol
{
	HTTP,
	HTTPS
};

std::string ProtocolToString(Protocol protocol);

Protocol StringToProtocol(const std::string& str);