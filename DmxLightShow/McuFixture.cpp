#include "McuFixture.h"



McuFixture::McuFixture()
{
}


McuFixture::~McuFixture()
{
}


/* override */ const char* McuFixture::GetName1()
{
	return 0;
}


/* override */ const char* McuFixture::GetName2()
{
	return 0;
}


/* override */ const char* McuFixture::GetAbbr()
{
	return 0;
}


/* override */ int McuFixture::GetX()
{
	return 0;
}


/* override */ int McuFixture::GetY()
{
	return 0;
}


/* override */ void McuFixture::SetProperties(
	const char* name1, const char* name2, const char* abbr, int x, int y)
{
	(void)name1;
	(void)name2;
	(void)abbr;
	(void)x;
	(void)y;
}


/* override */ void McuFixture::StroboChanged()
{
}


/* override */ bool McuFixture::GetAtLeastOneStepIncreased()
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
