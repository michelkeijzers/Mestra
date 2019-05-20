// CharUtils.h
// Utilities for a single character.

#pragma once

class CharUtils
{
private:
	CharUtils();
	~CharUtils();

public:
	static char ToUpper(char ch);
	static char ToLower(char ch);

	static char* TrimWhitespace(char* str);
};

