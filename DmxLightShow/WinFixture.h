// TestFixture.h
// Only for Windows.

#pragma once

#include "PlatformFixture.h"

#define MAX_NAME_LENGTH 128

class WinFixture : public PlatformFixture
{
public:
	WinFixture();

	virtual ~WinFixture();
	
	const char* GetName1();
	const char* GetName2();
	const char* GetAbbr();

	/* override */ uint16_t GetX();
	/* override */ uint16_t GetY();

	/* override */ void SetProperties(const char* name1, const char* name2, const char* abbr,
		uint16_t x, uint16_t y);

	/* override */ bool HasColorChanged();
	/* override */ void SetColorChanged(bool changed);

	/* override */ void StroboChanged();
	
	/* override */ bool GetAtLeastOneStepIncreased();
	/* override */ void ResetAtLeastOneStepIncreased();
	/* override */ void PostProcessCheckIncreaseStep(bool increased);

protected:
	// Name (2 lines) and abbreviation.
	char _name1[MAX_NAME_LENGTH];
	char _name2[MAX_NAME_LENGTH];
	char _abbr[MAX_NAME_LENGTH];

	// Coordinates on screen.
	uint16_t _x;
	uint16_t _y;

	bool _colorHasChanged;

	bool _atLeastOneStepIncreased;
};

