#pragma once


#include "stdio.h"
#include "Windows.h"


// Decimal
#define DEC 1
#define HEX 2


class SerialClass
{
public:
	void println(const char* str);
	void println(int value);
	void println(int value, int mode);

	void print(const char* str);
	void print(int value);
	void print(int value, int mode);

	void flush();

private:
	wchar_t _message[256];
	wchar_t _string[256];
};


extern SerialClass Serial;

