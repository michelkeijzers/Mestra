// Fixture.h
// Generic properties for a fixture.
// Only for Windows.

#ifdef _WINDOWS


#include <string>
#include "ClassNames.h"
#include HEADER_FILE(LIGHT_SETUP_CLASS)
#include "WinFixture.h"
#include "Par.h"


WinFixture::WinFixture()
	: _x(0),
	  _y(0),
	  _atLeastOneStepIncreased(false)
{
	_name1[0] = '\0';
	_name2[0] = '\0';
	_abbr[0] = '\0';
}


WinFixture::~WinFixture()
{
}


/* override */ void WinFixture::SetProperties(
	const char* name1, const char* name2, const char* abbr, int x, int y)
{
	strcpy_s(_name1, name1);
	strcpy_s(_name2, name2);
	strcpy_s(_abbr, abbr);

	_x = x;
	_y = y;	
	_atLeastOneStepIncreased = false;
}


void WinFixture::PostProcessCheckIncreaseStep(bool increased)
{
	if (increased)
	{
		_atLeastOneStepIncreased = true;
	}
}

#endif // _WINDOWS
