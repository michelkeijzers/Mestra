#pragma once

#define FILE_WRITE 0


class File
{
public:
	File();
	~File();

	void close();

	void println(int val);

	operator bool() const;
};


class SdStub
{
public:
	SdStub();
	~SdStub();

	File open(const char* fileName, int fileMode);
	bool begin(int csPin);
};

extern SdStub SD;