// TestFixture.h
// Only for Windows.

#pragma once

#include "PlatformFixture.h"

#define WIN_FIXTURE_MAX_NAME_LENGTH 128

class WinFixture : public PlatformFixture
{
public:
	WinFixture();

	virtual ~WinFixture();
	
	const char* GetName1() const override;
	const char* GetName2() const override;
	const char* GetAbbr() const override;

	uint16_t GetX() const override;
	uint16_t GetY() const override;

	void SetProperties(const char* name1, const char* name2, const char* abbr,
		uint16_t x, uint16_t y) override;

	bool HasColorChanged() const override;
	void SetColorChanged(bool changed) override;

	void StroboChanged() override;
	
	bool GetAtLeastOneStepIncreased() const override;
	void ResetAtLeastOneStepIncreased() override;
	void PostProcessCheckIncreaseStep(bool increased) override;

protected:
	// Name (2 lines) and abbreviation.
	char _name1[WIN_FIXTURE_MAX_NAME_LENGTH];
	char _name2[WIN_FIXTURE_MAX_NAME_LENGTH];
	char _abbr[WIN_FIXTURE_MAX_NAME_LENGTH];

	// Coordinates on screen.
	uint16_t _x;
	uint16_t _y;

	bool _colorHasChanged;

	bool _atLeastOneStepIncreased;
};

