// StringUtils.cpp
// String/char array utilities

#include <ctype.h>
#include <string.h>
#include "CharUtils.h"
#include "StringUtils.h"

/**
 * -1 if not found, else index, only checks a-z, no capitals
 */
/* static */ int8_t StringUtils::GetIndexOfLastLetter(const char* text, uint8_t length)
{
	for (int8_t index = length - 1; index >= 0; index--)
	{
		char character = CharUtils::ToLower(text[index]);
		if ((character >= 'a') && (character <= 'z'))
		{
			return index;
		}
	}

	return -1;
}



/* static */ char* StringUtils::TrimWhitespace(char* str)
{
	char* end;

	// Trim leading space
	while (isspace((unsigned char)* str))
	{
		str++;
	}

	if (*str == 0)  // All spaces?
	{
		return str;
	}

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)* end))
	{
		end--;
	}

	// Write new null terminator character
	end[1] = '\0';

	return str;
}


/* static */ void StringUtils::ToUpper(char* str) 
{
	while (*str) 
	{
		*str = CharUtils::ToUpper((unsigned char) str[0]);
		str++;
	}
}


/* static */ void StringUtils::ToLower(char* str)
{
	while (*str)
	{
		*str = CharUtils::ToLower((unsigned char)str[0]);
		str++;
	}
}