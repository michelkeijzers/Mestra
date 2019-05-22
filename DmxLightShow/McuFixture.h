#pragma once

#include "mcuFixture.h"
#include "PlatformFixture.h"

class McuFixture : public PlatformFixture
{
public:
	McuFixture();
	~McuFixture();

	/* override */ const char* GetName1();
	/* override */ const char* GetName2();
	/* override */ const char* GetAbbr();

	/* override */ int GetX();
  /* override */ int GetY();

	/* override */ void SetProperties(
		const char* name1, const char* name2, const char* abbr, int x, int y);

	/* override */ bool HasColorChanged();
	/* override */ void SetColorChanged(bool changed);

	/* override */ void StroboChanged();

	/* override */ bool GetAtLeastOneStepIncreased();
	/* override */ void ResetAtLeastOneStepIncreased();
	/* override */ void PostProcessCheckIncreaseStep(bool increased);
};

