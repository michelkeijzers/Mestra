// StringUtils.h
// String/char array utilities

#pragma once


#include <stdint.h>


class StringUtils
{
public:
private:
	StringUtils() { }

	~StringUtils() { }

public:
	static int8_t GetIndexOfLastLetter(const char* text, uint8_t length);

	static char* TrimWhitespace(char* str);

	static void ToUpper(char* str);

	static void ToLower(char* str);
};

