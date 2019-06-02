#pragma once

#include "mcuFixture.h"
#include "PlatformFixture.h"

class McuFixture : public PlatformFixture
{
public:
	McuFixture();
	virtual ~McuFixture();

	/* override */ const char* GetName1();
	/* override */ const char* GetName2();
	/* override */ const char* GetAbbr();

	/* override */ uint16_t GetX();
  /* override */ uint16_t GetY();

	/* override */ void SetProperties(
		const char* name1, const char* name2, const char* abbr, uint16_t x, uint16_t y);

	/* override */ bool HasColorChanged();
	/* override */ void SetColorChanged(bool changed);

	/* override */ void StroboChanged();

	/* override */ bool GetAtLeastOneStepIncreased();
	/* override */ void ResetAtLeastOneStepIncreased();
	/* override */ void PostProcessCheckIncreaseStep(bool increased);
};

