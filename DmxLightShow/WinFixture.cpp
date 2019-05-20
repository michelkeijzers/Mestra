// Fixture.h
// Generic properties for a fixture.
// Only for Windows.

#ifdef _WINDOWS


#include <string>
#include "ClassNames.h"
#include "LightSetup.h"
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


const char* WinFixture::GetName1() 
{
	return _name1; 
}


const char* WinFixture::GetName2() 
{
	return _name2; 
}


const char* WinFixture::GetAbbr()
{
	return _abbr; 
}


int WinFixture::GetX()
{
	return _x; 
}


int WinFixture::GetY() 
{
	return _y; 
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


/* virtual */ void WinFixture::StroboChanged()
{
	_atLeastOneStepIncreased = true;
}


bool WinFixture::GetAtLeastOneStepIncreased()
{
	return _atLeastOneStepIncreased;
}


void WinFixture::ResetAtLeastOneStepIncreased()
{
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
