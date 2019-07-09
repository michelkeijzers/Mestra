// Fixture.h
// Generic properties for a fixture.
// Only for Windows.

#include <string.h>
#ifdef _WINDOWS


#include <string>
#include "WinFixture.h"


WinFixture::WinFixture()
	:
	_x(0),
	_y(0),
	_colorHasChanged(false),
	_atLeastOneStepIncreased(false)
{
	_name1[0] = '\0';
	_name2[0] = '\0';
	_abbr[0] = '\0';
}


WinFixture::~WinFixture()
{
}


/* override */ const char* WinFixture::GetName1() const
{
	return _name1; 
}


/* override */ const char* WinFixture::GetName2() const
{
	return _name2; 
}


/* override */ const char* WinFixture::GetAbbr() const
{
	return _abbr; 
}


/* override */ uint16_t WinFixture::GetX() const
{
	return _x; 
}


/* override */ uint16_t WinFixture::GetY() const
{
	return _y; 
}


/* override */ void WinFixture::SetProperties(
	const char* name1, const char* name2, const char* abbr, uint16_t x, uint16_t y)
{
	strcpy_s(_name1, name1);
	strcpy_s(_name2, name2);
	strcpy_s(_abbr, abbr);

	_x = x;
	_y = y;
	_atLeastOneStepIncreased = false;
}


/* override */ bool WinFixture::HasColorChanged() const
{
	return _colorHasChanged;
}


/* override */ void WinFixture::SetColorChanged(bool changed)
{
	_colorHasChanged = changed;
}


/* override */ void WinFixture::StroboChanged()
{
	_atLeastOneStepIncreased = true;
}


/* override */ bool WinFixture::GetAtLeastOneStepIncreased() const
{
	return _atLeastOneStepIncreased;
}


/* override */ void WinFixture::ResetAtLeastOneStepIncreased()
{
	_atLeastOneStepIncreased = false;
}


/* override */ void WinFixture::PostProcessCheckIncreaseStep(bool increased)
{
	if (increased)
	{
		_atLeastOneStepIncreased = true;
	}
}

#endif // _WINDOWS
