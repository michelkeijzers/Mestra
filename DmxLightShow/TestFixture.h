// TestFixture.h
// Only for Windows.

#pragma once


#include "Fixture.h"


#define MAX_NAME_LENGTH 128


class TestFixture : public Fixture
{
protected:
	// Name (2 lines) and abbreviation.
	char _name1[MAX_NAME_LENGTH];
	char _name2[MAX_NAME_LENGTH];
	char _abbr[MAX_NAME_LENGTH];

	// Coordinates on screen.
	int _x;

	int _y;

	bool _atLeastOneStepIncreased;

public:
	TestFixture();

	~TestFixture();

	const char* GetName1() { return _name1; }

	const char* GetName2() { return _name2; }

	const char* GetAbbr() { return _abbr; }


	int GetX() { return _x; }

	int GetY() { return _y; }

	void SetProperties(const char* name1, const char* name2, const char* abbr,
		int x, int y);

	/* override */ bool CheckIncreaseStep();

	/* virtual */ void StroboChanged() { _atLeastOneStepIncreased = true; }

	bool GetAtLeastOneStepIncreased() { return _atLeastOneStepIncreased; }
	
	void ResetAtLeastOneStepIncreased() { _atLeastOneStepIncreased = false; }
};
