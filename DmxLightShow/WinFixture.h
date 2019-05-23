// TestFixture.h
// Only for Windows.

#pragma once

#include "PlatformFixture.h"

#define MAX_NAME_LENGTH 128

class WinFixture : public PlatformFixture
{
public:
	WinFixture();

	~WinFixture();
	
	const char* GetName1();
	const char* GetName2();
	const char* GetAbbr();

	/* override */ int GetX();
	/* override */ int GetY();

	/* override */ void SetProperties(const char* name1, const char* name2, const char* abbr,
		int x, int y);

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
	int _x;
	int _y;

	bool _colorHasChanged;

	bool _atLeastOneStepIncreased;
};
