#ifdef _WINDOWS


#include "SdStub.h"
#include <stdio.h>


SdStub SD;


File _file;


File::File()
{

}


File::~File()
{

}


void File::close()
{
}


void File::println(int val)
{
	printf("%d\n", val);
}


File::operator bool() const
{
	return true;
}



SdStub::SdStub()
{
}


SdStub::~SdStub()
{
}


File SdStub::open(const char* fileName, int fileMode)
{
	printf("File name: %s\n", fileName);
	printf("File mode: %d\n", fileMode);

	return _file;
}


bool SdStub::begin(int csPin)
{
	printf("SD pin: %d\n", csPin);
	return true;
}


#endif // _WINDOWS