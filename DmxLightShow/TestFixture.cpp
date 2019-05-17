// Fixture.h
// Generic properties for a fixture.
// Only for Windows.

#ifdef _WINDOWS


#include <string>
#include "ClassNames.h"
#include HEADER_FILE(LIGHT_SETUP_CLASS)
#include "TestFixture.h"
#include "Par.h"


TestFixture::TestFixture()
{
	_name1[0] = '\0';
	_name2[0] = '\0';
	_abbr[0] = '\0';

	_x = 0;
	_y = 0;
}


TestFixture::~TestFixture()
{
}


void TestFixture::SetProperties(
	const char* name1, const char* name2, const char* abbr,
	uint8_t x, uint8_t y)
{
	strcpy_s(_name1, name1);
	strcpy_s(_name2, name2);
	strcpy_s(_abbr, abbr);

	_x = x;
	_y = y;	
}


bool TestFixture::CheckIncreaseStep()
{
	bool increased = Fixture::CheckIncreaseStep();
	if (increased)
	{
		LightSetup.Print();
	}

	return increased;
}

#endif // _WINDOWS
