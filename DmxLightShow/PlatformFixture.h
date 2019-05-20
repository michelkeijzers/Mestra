#pragma once
/* abstract */ class PlatformFixture
{
public:
	PlatformFixture();
	~PlatformFixture();

	virtual const char* GetName1() = 0;
	virtual const char* GetName2() = 0;
	virtual const char* GetAbbr() = 0;

	virtual int GetX() = 0;
	virtual int GetY() = 0;

	virtual void SetProperties(
		const char* name1, const char* name2, const char* abbr, int x, int y) = 0;

	virtual void StroboChanged() = 0;

	virtual bool GetAtLeastOneStepIncreased() = 0;
	virtual void ResetAtLeastOneStepIncreased() = 0;

	virtual void PostProcessCheckIncreaseStep(bool increased) = 0;
};

