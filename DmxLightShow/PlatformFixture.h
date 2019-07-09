#pragma once

#include "MestraTypes.h"


/* abstract */ class PlatformFixture
{
public:
	PlatformFixture();
	virtual ~PlatformFixture();

	virtual const char* GetName1() const = 0;
	virtual const char* GetName2() const = 0;
	virtual const char* GetAbbr() const = 0;

	virtual uint16_t GetX() const = 0;
	virtual uint16_t GetY() const = 0;

	virtual void SetProperties(
		const char* name1, const char* name2, const char* abbr, uint16_t x, uint16_t y) = 0;

	virtual bool HasColorChanged() const = 0;
	virtual void SetColorChanged(bool changed) = 0;

	virtual void StroboChanged() = 0;

	virtual bool GetAtLeastOneStepIncreased() const = 0;
	virtual void ResetAtLeastOneStepIncreased() = 0;

	virtual void PostProcessCheckIncreaseStep(bool increased) = 0;
};
