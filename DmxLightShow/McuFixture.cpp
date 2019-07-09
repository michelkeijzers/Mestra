#include "McuFixture.h"



McuFixture::McuFixture()
{
}


McuFixture::~McuFixture()
{
}


/* override */ const char* McuFixture::GetName1() const
{
	return nullptr;
}


/* override */ const char* McuFixture::GetName2() const
{
	return nullptr;
}


/* override */ const char* McuFixture::GetAbbr() const
{
	return nullptr;
}


/* override */ uint16_t McuFixture::GetX() const
{
	return 0;
}


/* override */ uint16_t McuFixture::GetY() const
{
	return 0;
}


/* override */ void McuFixture::SetProperties(
	const char* name1, const char* name2, const char* abbr, uint16_t x, uint16_t y)
{
	(void)name1;
	(void)name2;
	(void)abbr;
	(void)x;
	(void)y;
}


/* override */ bool McuFixture::HasColorChanged() const
{
	return true;
}


/* override */ void McuFixture::SetColorChanged(bool changed)
{
	(void)changed;
}


/* override */ void McuFixture::StroboChanged()
{
}


/* override */ bool McuFixture::GetAtLeastOneStepIncreased() const
{
	return false;
}


/* override */ void McuFixture::ResetAtLeastOneStepIncreased()
{

}


/* override */ void McuFixture::PostProcessCheckIncreaseStep(bool increased)
{
	(void)increased;
}
