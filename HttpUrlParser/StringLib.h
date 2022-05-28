#pragma once
#include <algorithm>
#include <string>

inline std::string ToLowerCase(std::string str) noexcept
{
	std::transform(str.begin(), str.end(), str.begin(), [](char c) {
		return std::tolower(c);
	});
	return str;
}