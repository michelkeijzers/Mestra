#pragma once

#include "mcuFixture.h"
#include "PlatformFixture.h"

class McuFixture : public PlatformFixture
{
public:
	McuFixture();
	virtual ~McuFixture();

	const char* GetName1() const override;
	const char* GetName2() const override;
	const char* GetAbbr() const override;

	uint16_t GetX() const override;
	uint16_t GetY() const override;

	void SetProperties(
		const char* name1, const char* name2, const char* abbr, uint16_t x, uint16_t y) override;

	bool HasColorChanged() const override;
	void SetColorChanged(bool changed) override;
	
	void StroboChanged() override;
	
	bool GetAtLeastOneStepIncreased() const override;
	void ResetAtLeastOneStepIncreased() override;
	void PostProcessCheckIncreaseStep(bool increased) override;
};

