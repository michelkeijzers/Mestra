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
	uint8_t _x;
	uint8_t _y;

public:
	TestFixture();

	~TestFixture();

	const char* GetName1() { return _name1; }

	const char* GetName2() { return _name2; }

	const char* GetAbbr() { return _abbr; }


	uint8_t GetX() { return _x; }

	uint8_t GetY() { return _y; }

	void SetProperties(const char* name1, const char* name2, const char* abbr,
		uint8_t x, uint8_t y);

	/* override */ bool CheckIncreaseStep();
};
