#include "Parser.h"
#include <iostream>

net::Parser::Parser()
{}

net::Header net::Parser::Parse(std::string const& header) const
{
	Header result;
	size_t i = 0U;
	for (; i < header.size() && header[i] != ' '; ++i) {
		result.Method += header[i];
	}

	uint8_t charLen = 0;
	uint16_t charCode = 0;
	for (++i; i < header.size() && header[i] != ' ' && header[i] != '?'; ++i) {
		if (header[i] == '%') {
			charLen = 2;
			charCode = 0;
		}
		else if (charLen > 0) {
			charCode <<= 4;
			if ('0' <= header[i] && header[i] <= '9') {
				charCode += header[i] - '0';
			}
			else if ('A' <= header[i] && header[i] <= 'F') {
				charCode += header[i] - 'A' + 10;
			}
			else if ('a' <= header[i] && header[i] <= 'f') {
				charCode += header[i] - 'a' + 10;
			}
			--charLen;
			if (charLen == 0) {
				result.Path += std::wctob(charCode);
			}
		}
		else {
			result.Path += header[i];
		}
	}
	return result;
}
